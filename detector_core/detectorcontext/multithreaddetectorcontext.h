#pragma once
#include "detector_global.h"
#include "detectorcontext.h"
#include <thread>

using namespace std;

class DetectorContextCore;
class DETECTOR_EXPORT MultiThreadDetectorContext final : public DetectorContext
{
public:
    explicit MultiThreadDetectorContext(const string& resultDir, const int numberOfConcurrent = std::thread::hardware_concurrency());
    virtual DetectorRuleNames getDetectorRuleNames() override;
protected:
    virtual pair<bool, string> init(const DetectorRuleNames& detectorRuleNames) override;
    virtual bool detectCore(const vector<CPPPathPair>& pathPairs) override;
    virtual DetectorErrors getDetectorErrorsCore() override;
    virtual DetectorRuleContents getDetectorRuleContents() override;

    void detectorConcurrentCore(atomic_int& index, const vector<CPPPathPair>& pathPairs, int i);
    int getIndex(atomic_int& index);
private:
    vector<shared_ptr<DetectorContextCore>> m_contextCores;
    int m_numberOfConcurrent = 0;
    std::mutex m_mutex;
};