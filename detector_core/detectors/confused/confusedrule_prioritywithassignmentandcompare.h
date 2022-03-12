#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"

class IfDefinition;
class DETECTOR_EXPORT ConfusedRulePriorityWithAssignmentAndCompare final : public Rule {
public:
    ConfusedRulePriorityWithAssignmentAndCompare();
    ~ConfusedRulePriorityWithAssignmentAndCompare();
    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;
    void resetData() override;

private:
    std::unique_ptr<IfDefinition> m_ifDefinition;
};

REGISTER_CLASS(ConfusedRulePriorityWithAssignmentAndCompare)
