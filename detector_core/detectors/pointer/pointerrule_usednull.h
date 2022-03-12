#pragma once
#include "../rule.h"
#include "common/reflecter.h"
#include "pointerrule_useduninitializedornull.h"
#include "detector_global.h"

class DETECTOR_EXPORT PointerRuleUsedNull final : public PointerRuleUsedUninitializedOrNull {
public:
    PointerRuleUsedNull();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;
};

REGISTER_CLASS(PointerRuleUsedNull)