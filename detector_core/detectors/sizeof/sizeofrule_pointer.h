#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include <string>

class VariableDefinition;
class SizeOfRulePointer final : public Rule {
public:
    SizeOfRulePointer();
    ~SizeOfRulePointer();
    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::set<std::string> m_variableNames;
    std::unique_ptr<VariableDefinition> m_variableDefinition;
};

REGISTER_CLASS(SizeOfRulePointer)
