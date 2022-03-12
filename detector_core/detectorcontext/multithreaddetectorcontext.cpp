#include "multithreaddetectorcontext.h"
#include "common/filehelp.h"
#include "detectorcontextcore.h"
#include <iosfwd>
#include <sstream>

MultiThreadDetectorContext::MultiThreadDetectorContext(const string& resultDir, const int numberOfConcurrent /*= std::thread::hardware_concurrency()*/)
    : DetectorContext(resultDir, "results.json")
    , m_numberOfConcurrent(numberOfConcurrent)
{
    for (auto i = 0; i < m_numberOfConcurrent; i++)
    {
        m_contextCores.emplace_back(make_shared<DetectorContextCore>(unique_ptr<IFile>(make_unique<FileHelp>())));
    }
}

DetectorRuleNames MultiThreadDetectorContext::getDetectorRuleNames()
{
    return m_contextCores[0]->getDetectorRuleNames();
}

std::pair<bool, std::string> MultiThreadDetectorContext::init(const DetectorRuleNames& detectorRuleNames)
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

bool MultiThreadDetectorContext::detectCore(const vector<CPPPathPair>& pathPairs)
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

void MultiThreadDetectorContext::detectorConcurrentCore(atomic_int& index, const vector<CPPPathPair>& pathPairs, int i)
{
    while (index < pathPairs.size())
    {
        auto indexTmp = getIndex(index);
        std::ostringstream oss;
        oss << std::this_thread::get_id();
        CPPPathPair pathPair = pathPairs[indexTmp];
        string msg = to_string(indexTmp) + "," + pathPair.header + "," + pathPair.source + oss.str() + "\n";
        std::cout << msg;
        m_contextCores[i]->detect(pathPair);
    }
}

int MultiThreadDetectorContext::getIndex(atomic_int& index)
{
    std::lock_guard<std::mutex> lck(m_mutex);
    auto indexTmp = index++;
    return indexTmp;
}

DetectorErrors MultiThreadDetectorContext::getDetectorErrorsCore()
{
    DetectorErrors detectorErrors;
    for (const auto& item : m_contextCores)
    {
        auto errors = item->getDetectorErrors();
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
    }
    return detectorErrors;
}

DetectorRuleContents MultiThreadDetectorContext::getDetectorRuleContents()
{
    return m_contextCores[0]->getDetectorRuleContents();
}