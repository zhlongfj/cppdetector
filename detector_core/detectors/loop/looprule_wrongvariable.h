#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"

class LoopRuleWrongVariable final : public Rule {
public:
    LoopRuleWrongVariable();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;
};

REGISTER_CLASS(LoopRuleWrongVariable)
