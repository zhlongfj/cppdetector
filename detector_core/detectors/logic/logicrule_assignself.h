#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"

class LogicRuleAssignSelf final : public Rule {
public:
    LogicRuleAssignSelf();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;
};

REGISTER_CLASS(LogicRuleAssignSelf)
