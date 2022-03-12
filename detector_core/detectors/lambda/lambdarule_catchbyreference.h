#pragma once
#include "detectors/rule.h"
#include "../../common/reflecter.h"

class LambdaRuleCatchByReference final : public Rule {
public:
    LambdaRuleCatchByReference();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;
};

REGISTER_CLASS(LambdaRuleCatchByReference)
