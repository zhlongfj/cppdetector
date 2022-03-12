#pragma once
#include "../rule.h"
#include "common/reflecter.h"
#include "pointerrule_useduninitializedornull.h"

class PointerRuleUsedUninitialized final : public PointerRuleUsedUninitializedOrNull {
public:
    PointerRuleUsedUninitialized();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;
};

REGISTER_CLASS(PointerRuleUsedUninitialized)