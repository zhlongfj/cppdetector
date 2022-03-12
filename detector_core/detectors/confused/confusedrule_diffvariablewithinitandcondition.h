#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"

class DETECTOR_EXPORT ConfusedRuleDiffVariableWithInitAndCondition final: public Rule {
public:
    ConfusedRuleDiffVariableWithInitAndCondition();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;
};

REGISTER_CLASS(ConfusedRuleDiffVariableWithInitAndCondition)
