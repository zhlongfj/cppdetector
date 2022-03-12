#include <detectorcontext/detectorcontext.h>
#include <common/filehelp.h>
#include <detectorcommon/cpppath.h>
#include <filesystem>
#include <iosfwd>
#include <iostream>
#include "atomic"
#include <thread>
#include "common/filepathhelper.h"
#include "detectorcommon/detectorcommon.h"

using namespace std;

int64_t getCurrentMilliseconds()
{
    typedef chrono::time_point<chrono::system_clock, chrono::milliseconds> microClock_type;
    microClock_type tp = chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now());
    return tp.time_since_epoch().count();
}

DetectorContext::DetectorContext(const string& resultDir, const string& resultName)
    : m_resultDir(resultDir)
    , m_resultName(resultName)
{
}

DetectorErrors DetectorContext::detectAll(const string& codePath)
{
    return detectWithRuleNames(codePath, getDetectorRuleNames());
}

bool DetectorContext::existErrorResults(const DetectorErrors& errors)
{
    for (const auto& element : errors)
    {
        vector<shared_ptr<RuleError>> ruleErrors = element.second;
        auto iter = find_if(ruleErrors.begin(), ruleErrors.end(), [&ruleErrors](const auto& error) {
            auto priority = error->ruleContent->priority;
            return priority == ErrorPriority::Critical || priority == ErrorPriority::Error;
            });
        if (iter != ruleErrors.cend())
        {
            return true;
        }
    }
    return false;
}

DetectorErrors DetectorContext::detectWithRuleNamePath(const string& codePath, const string& ruleNamePath)
{
    m_ruleNamePath = ruleNamePath;
    auto ruleNames = DetectorCommon().getDetectorRuleNames(ruleNamePath);
    if (ruleNames.empty())
    {
        ruleNames = getDetectorRuleNames();
    }
    return detectWithRuleNames(codePath, ruleNames);
}

DetectorErrors DetectorContext::detectWithRuleNames(const string& codePath, const DetectorRuleNames& detectorRuleNames)
{
    const string& resultDir = m_resultDir;
    filesystem::remove_all(resultDir);
    if (!filesystem::exists(resultDir))
    {
        filesystem::create_directory(resultDir);
    }

    auto ret = init(detectorRuleNames);
    if (!ret.first)
    {
        std::cout << ret.second << std::endl;
        return DetectorErrors();
    }

    detect(codePath);
    auto detectorErrors = getDetectorErrors();
    DetectorCommon().setDetectorErrors((filesystem::path(resultDir) / m_resultName).string(), detectorErrors);
    return detectorErrors;
}

vector<string> DetectorContext::setExceptionConfigPath(const string& configPath)
{
    m_exceptionPaths = DetectorCommon().getPathsFromConfigPath(configPath);
    return m_exceptionPaths;
}

bool DetectorContext::detect(const string& codePath)
{
    std::vector<CPPPathPair> pathPairs;
    if (codePath.find(".json") != string::npos)
    {
        pathPairs = makePathPairFromJSONPath(codePath);
    }
    else
    {
        pathPairs = makePathPairFromDir(codePath);
    }
    sort(pathPairs.begin(), pathPairs.end(), [this](const CPPPathPair& left, const CPPPathPair& right) {
        return getSizeFromPath(left.header) + getSizeFromPath(left.source) > getSizeFromPath(right.header) + getSizeFromPath(right.source);
        });
    auto time1 = getCurrentMilliseconds();

    bool ret = detectCore(pathPairs);
    std::cout << "detect Time: " << getCurrentMilliseconds() - time1 << std::endl;
    return ret;
}

uintmax_t DetectorContext::getSizeFromPath(const string& filePath)
{
    try
    {
        return !filePath.empty() ? filesystem::file_size(filesystem::path(filePath)) : 0;
    }
    catch (const std::exception&)
    {
        return 0;
    }
}

std::vector<CPPPathPair> DetectorContext::makePathPairFromDir(const string& codePath)
{
    vector<string> codePaths = CPPPath(codePath).getFilePaths();
    return makePathPair(codePaths);
}

std::vector<CPPPathPair> DetectorContext::makePathPairFromJSONPath(const string& jsonPath)
{
    vector<string> codePaths = DetectorCommon().getPathsFromConfigPath(jsonPath);
    codePaths.erase(remove_if(codePaths.begin(), codePaths.end(), [](const string& element) {
        return !exists(path(element)) || !CPPPath::isCPPCodeFile(element);
        }), codePaths.end());
    return makePathPair(codePaths);
}

std::vector<CPPPathPair> DetectorContext::makePathPair(const vector<string>& codePaths)
{
    vector<CPPPathPair> pathPairs;
    string lastFileName;
    for (const auto& item : codePaths)
    {
        if (isExceptionPath(item))
        {
            continue;
        }
        filesystem::path path(item);
        CPPPathPair pathPair;
        auto fileName = path.stem().string();
        bool isPair = !lastFileName.empty()
            && lastFileName == fileName;
        lastFileName = fileName;
        if (isPair)
        {
            pathPairs[pathPairs.size() - 1].source = path.string();
            continue;
        }
        if (path.extension().string().find("h") != string::npos)
        {
            pathPair.header = path.string();
        }
        else
        {
            pathPair.source = path.string();
        }
        pathPairs.emplace_back(pathPair);
    }
    return pathPairs;
}

bool DetectorContext::isExceptionPath(const string& path)
{
    for (const auto& item : m_exceptionPaths)
    {
        auto helper = FilePathHelper(item);
        if (!helper.exist())
        {
            continue;
        }
        if (helper.fileType() == file_type::regular)
        {
            if (path == item)
            {
                return true;
            }
        }
        else
        {
            if (path.find(item) != string::npos)
            {
                return true;
            }
        }
    }

    return false;
}

DetectorErrors DetectorContext::getDetectorErrors()
{
    auto time1 = getCurrentMilliseconds();
    DetectorErrors detectorErrors = getDetectorErrorsCore();
    std::cout << "getDetectorErrors time: " << getCurrentMilliseconds() - time1 << std::endl;
    return detectorErrors;
}