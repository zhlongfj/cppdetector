#pragma once
#include "detector_global.h"
#include "detectorcontext.h"

using namespace std;

class DetectorContextCore;
class DETECTOR_EXPORT SingleThreadDetectorContext final : public DetectorContext
{
public:
    explicit SingleThreadDetectorContext(const string& resultDir);
    virtual DetectorRuleNames getDetectorRuleNames() override;
    DetectorErrors detectFromApp(const string& header, const string& source, const string& ruleNamePath);
protected:
    virtual DetectorErrors getDetectorErrorsCore() override;
    virtual DetectorRuleContents getDetectorRuleContents() override;
    virtual pair<bool, string> init(const DetectorRuleNames& detectorRuleNames) override;
    virtual bool detectCore(const vector<CPPPathPair>& pathPairs) override;
    void writeResultToFile(const DetectorErrors& detectorErrors, const CPPPathPair& cppPathPair);
private:
    shared_ptr<DetectorContextCore> m_contextCore;
};
