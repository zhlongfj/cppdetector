#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"

class OperationRuleZeroDivision final : public Rule {
public:
    OperationRuleZeroDivision();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;
};

REGISTER_CLASS(OperationRuleZeroDivision)
