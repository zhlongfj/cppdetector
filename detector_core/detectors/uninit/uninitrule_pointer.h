#pragma once
#include "../rule.h"
#include "common/reflecter.h"
#include <string>
#include "detector_global.h"

class UninitRuleVariableDefinitionHelper;
class VariableDefinition;
class DETECTOR_EXPORT UninitRulePointer final : public Rule {
public:
    UninitRulePointer();
    ~UninitRulePointer();
    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::unique_ptr<UninitRuleVariableDefinitionHelper> m_uninitRuleVarHelper;
    std::unique_ptr<VariableDefinition> m_definition;
};

REGISTER_CLASS(UninitRulePointer)
