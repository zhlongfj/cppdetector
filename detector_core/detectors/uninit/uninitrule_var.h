#pragma once
#include "../rule.h"
#include "common/reflecter.h"
#include <string>

class UninitRuleVariableDefinitionHelper;
class UninitRuleVar final : public Rule {
public:
    UninitRuleVar();
    ~UninitRuleVar();
    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::unique_ptr<UninitRuleVariableDefinitionHelper> m_uninitRuleVarHelper;
};

REGISTER_CLASS(UninitRuleVar)
