#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"

class IfDefinition;
class ConditionContext;
class DETECTOR_EXPORT ConfusedRuleConditionRepeat final : public Rule {
public:
    ConfusedRuleConditionRepeat();
    ~ConfusedRuleConditionRepeat();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    bool checkOperand(const std::string& condition, const std::string& operand);
    bool assignToOperand(const string& code, const string& operand);
    std::unique_ptr<IfDefinition> m_ifDefinition;
    std::vector<ConditionContext> m_conditionContexts;

    std::map<std::string, size_t> m_conditions;
};

REGISTER_CLASS(ConfusedRuleConditionRepeat)
