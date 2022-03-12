#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"

class LogicRuleBaseValue final : public Rule {
public:
    LogicRuleBaseValue();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;
};

REGISTER_CLASS(LogicRuleBaseValue)
