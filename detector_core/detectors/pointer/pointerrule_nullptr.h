#pragma once
#include "../rule.h" 
#include "common/reflecter.h"

class PointerRuleNullptr final : public Rule {
public:
    PointerRuleNullptr();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;
};

REGISTER_CLASS(PointerRuleNullptr)
