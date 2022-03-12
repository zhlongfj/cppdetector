#include "multiprocessdetectorcontext.h"
#include "common/filehelp.h"
#include "detectorcontextcore.h"
#include "common/filepath.h"
#include <iosfwd>
#include <sstream>

MultiProcessDetectorContext::MultiProcessDetectorContext(const string& resultDir, const string& appPath, const int numberOfConcurrent /*= std::thread::hardware_concurrency()*/)
    : DetectorContext(resultDir, "results.json")
    , m_appPath(appPath)
    , m_numberOfConcurrent(numberOfConcurrent)
{
    //"For IO intensive applications, thread size is set to 2N+1" "For CPU-intensive applications, thread size is set to N+1"
    //test result:
    //cout + 1  time: 111383
    //count * 1.5 time : 108234
    //cout(8)   time : 108161
    //7         time : 109973
    //5         time : 110153
    for (auto i = 0; i < m_numberOfConcurrent; i++)
    {
        m_contextCores.emplace_back(make_shared<DetectorContextCore>(unique_ptr<IFile>(make_unique<FileHelp>())));
    }
}

DetectorRuleNames MultiProcessDetectorContext::getDetectorRuleNames()
{
    return m_contextCores[0]->getDetectorRuleNames();
}

std::pair<bool, std::string> MultiProcessDetectorContext::init(const DetectorRuleNames& detectorRuleNames)
{
    pair<bool, std::string> ret;
    for (const auto& item : m_contextCores)
    {
        ret = item->init(detectorRuleNames);
        if (!ret.first)
        {
            return ret;
        }
    }
    return ret;
}

bool MultiProcessDetectorContext::detectCore(const vector<CPPPathPair>& pathPairs)
{
    if (m_numberOfConcurrent > pathPairs.size())
    {
        m_numberOfConcurrent = pathPairs.size();
    }
    atomic_int index = 0;
    vector<std::thread> threads;
    for (auto i = 0; i < m_numberOfConcurrent; i++)
    {
        threads.emplace_back(
            std::thread(
                [this, &index, i, pathPairs]() {
                    detectorConcurrentCore(index, pathPairs, i);
                }
            )
        );
    }

    for (auto i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }

    return true;
}

void MultiProcessDetectorContext::detectorConcurrentCore(atomic_int& index, const vector<CPPPathPair>& pathPairs, int i)
{
    while (index < pathPairs.size())
    {
        auto indexTmp = getIndex(index);

        std::ostringstream oss;
        oss << std::this_thread::get_id();
        CPPPathPair pathPair = pathPairs[indexTmp];
        string msg = to_string(indexTmp) + "," + pathPair.header + "," + pathPair.source + oss.str() + "\n";
        std::cout << msg;

        auto type = " \"frommultiprocess\"";
        auto hpp = " \"" + pathPair.header + "\"";
        auto cpp = " \"" + pathPair.source + "\"";
        string ruleNamePath;
        if (!m_ruleNamePath.empty())
        {
            ruleNamePath = " \"" + m_ruleNamePath + "\"";
        }
        string parameter = type + hpp + cpp + ruleNamePath;
        system((m_appPath + parameter).c_str());
    }
}

int MultiProcessDetectorContext::getIndex(atomic_int& index)
{
    std::lock_guard<std::mutex> lck(m_mutex);
    auto indexTmp = index++;
    return indexTmp;
}

DetectorErrors MultiProcessDetectorContext::getDetectorErrorsCore()
{
    DetectorErrors detectorErrors;
    FilePath filePath(m_resultDir, [](std::filesystem::directory_entry item) {
        if (item.status().type() != filesystem::file_type::regular) {
            return false;
        }
        return true;
        });
    auto filePaths = filePath.getFilePaths();
#ifdef WIN32
    std::for_each(std::execution::par, std::begin(filePaths), std::end(filePaths), [this, &detectorErrors](const auto& item) {
#else
    std::for_each(std::begin(filePaths), std::end(filePaths), [this, &detectorErrors](const auto& item) {
#endif
        auto errors = DetectorCommon().getDetectorErrors(item);
        std::lock_guard<std::mutex> lck(m_mutex);
        for (const auto& item1 : errors)
        {
            if (detectorErrors.find(item1.first) == detectorErrors.end())
            {
                detectorErrors.insert(item1);
                continue;
            }
            auto& tempErrors = detectorErrors[item1.first];
            tempErrors.insert(tempErrors.end(), item1.second.begin(), item1.second.end());
        }
        });
    return detectorErrors;
}

DetectorRuleContents MultiProcessDetectorContext::getDetectorRuleContents()
{
    return m_contextCores[0]->getDetectorRuleContents();
}