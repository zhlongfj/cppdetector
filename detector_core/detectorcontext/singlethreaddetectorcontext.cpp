#include "common/filehelp.h"
#include "singlethreaddetectorcontext.h"
#include "detectorcontextcore.h"
#include <filesystem>

using namespace std;

SingleThreadDetectorContext::SingleThreadDetectorContext(const string& resultDir)
    : DetectorContext(resultDir, "results.json")
    , m_contextCore(make_unique<DetectorContextCore>(unique_ptr<IFile>(make_unique<FileHelp>())))
{
}

DetectorRuleNames SingleThreadDetectorContext::getDetectorRuleNames()
{
    return m_contextCore->getDetectorRuleNames();
}

DetectorErrors SingleThreadDetectorContext::getDetectorErrorsCore()
{
    DetectorErrors detectorErrors;
    auto errors = m_contextCore->getDetectorErrors();
    for (const auto& item : errors)
    {
        if (detectorErrors.find(item.first) == detectorErrors.end())
        {
            detectorErrors.insert(item);
            continue;
        }
        auto& tempErrors = detectorErrors[item.first];
        tempErrors.insert(tempErrors.end(), item.second.begin(), item.second.end());
    }

    return detectorErrors;
}

DetectorRuleContents SingleThreadDetectorContext::getDetectorRuleContents()
{
    return m_contextCore->getDetectorRuleContents();
}

std::pair<bool, std::string> SingleThreadDetectorContext::init(const DetectorRuleNames& detectorRuleNames)
{
    return m_contextCore->init(detectorRuleNames);
}

bool SingleThreadDetectorContext::detectCore(const vector<CPPPathPair>& pathPairs)
{
    bool ret = true;
    for (const auto& item : pathPairs)
    {
        string aa = item.header + "," + item.source + "\n";
        std::cout << aa;
        bool retTmp = m_contextCore->detect(item);
        if (!retTmp)
        {
            ret = false;
            std::cout << "detectCore Error: " << aa;
        }
    }

    return ret;
}

DetectorErrors SingleThreadDetectorContext::detectFromApp(const string& header, const string& source, const string& ruleNamePath)
{
    CPPPathPair cppPathPair(header, source);
    string pathPair = cppPathPair.header + "," + cppPathPair.source + "\n";
    std::cout << pathPair;

    auto detectorContentCore = DetectorContextCore(unique_ptr<IFile>(unique_ptr<FileHelp>()));
    auto ruleNames = detectorContentCore.getDetectorRuleNames();
    if (ruleNamePath.empty())
    {
        ruleNames = DetectorCommon().getDetectorRuleNames(ruleNamePath);
    }
    detectorContentCore.init(ruleNames);
    detectorContentCore.detect(cppPathPair);
    auto detectorErrors = detectorContentCore.getDetectorErrors();
    writeResultToFile(detectorErrors, cppPathPair);

    return detectorErrors;
}

void SingleThreadDetectorContext::writeResultToFile(const DetectorErrors& detectorErrors, const CPPPathPair& cppPathPair)
{
    if (detectorErrors.empty())
    {
        return;
    }

    auto tempresultDir = filesystem::path(m_resultDir) / "temp";
    if (!filesystem::exists(tempresultDir))
    {
        filesystem::create_directory(tempresultDir);
    }

    auto filePath = cppPathPair.header;
    if (filePath.empty())
    {
        filePath = cppPathPair.source;
        if (filePath.empty())
        {
            auto msg = "file name is empty";
            std::cout << msg << std::endl;
            throw msg;
        }
    }
    filesystem::path path(filePath);
    auto fileName = path.stem().string() + "_results.json";
    DetectorCommon().setDetectorErrors((tempresultDir / fileName).string(), detectorErrors);
}