#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"

class LogicRuleIncorrectOperation final : public Rule {
public:
    LogicRuleIncorrectOperation();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;
};

REGISTER_CLASS(LogicRuleIncorrectOperation)
