#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"

class OperationRuleBitwiseShiftToNegative final : public Rule {
public:
    OperationRuleBitwiseShiftToNegative();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    bool checkMinus(const std::string& content);
};

REGISTER_CLASS(OperationRuleBitwiseShiftToNegative)
