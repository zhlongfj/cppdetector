#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"

class DETECTOR_EXPORT LogicRuleExpressionRepetition final : public Rule {
public:
    LogicRuleExpressionRepetition();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;
};

REGISTER_CLASS(LogicRuleExpressionRepetition)
