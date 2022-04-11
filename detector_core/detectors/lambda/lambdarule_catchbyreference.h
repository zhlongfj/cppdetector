#pragma once
#include "detectors/rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"

class DETECTOR_EXPORT LambdaRuleCatchByReference final : public Rule {
public:
    LambdaRuleCatchByReference();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;
};

REGISTER_CLASS(LambdaRuleCatchByReference)
