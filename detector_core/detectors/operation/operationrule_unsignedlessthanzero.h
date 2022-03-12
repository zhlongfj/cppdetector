#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"

class OperationRuleUnsignedLessThanZero final : public Rule {
public:
    OperationRuleUnsignedLessThanZero();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::set<std::string> m_varNames;
};

REGISTER_CLASS(OperationRuleUnsignedLessThanZero)
