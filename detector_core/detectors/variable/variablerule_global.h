#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include <memory>
using namespace std;

class FunctionDefinition;
class ClassDefinition;

class DETECTOR_EXPORT VariableRuleGlobal final : public Rule {
public:
    VariableRuleGlobal();
    ~VariableRuleGlobal();
    bool detectCore(const string& code, const ErrorFile& errorFile) override;
    void resetData() override;

private:
    unique_ptr<FunctionDefinition> m_functionDefinition;
    unique_ptr<ClassDefinition> m_classDefinition;
};
REGISTER_CLASS(VariableRuleGlobal)
