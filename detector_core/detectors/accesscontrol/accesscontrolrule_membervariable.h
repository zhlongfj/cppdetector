#pragma once
#include <memory>
#include "../rule.h"
#include "../../common/reflecter.h"

using namespace std;

class ClassDefinition;
class VariableDefinition;

class DETECTOR_EXPORT AccessControlRuleMemberVariable final : public Rule {
public:
    AccessControlRuleMemberVariable();

    ~AccessControlRuleMemberVariable();

    bool detectCore(const string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::unique_ptr<ClassDefinition> classDefinition;
    std::unique_ptr<VariableDefinition> variableDefinition;
};
REGISTER_CLASS(AccessControlRuleMemberVariable)
