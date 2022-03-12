#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include <memory>
using namespace std;

class FunctionDefinition;
class ClassDefinition;

struct DETECTOR_EXPORT ErrorFileWithType
{
    bool isCopy = false;
    bool isMove = false;
    ErrorFile errorFile;
    void resetData()
    {
        isCopy = false;
        isMove = false;
        errorFile.resetData();
    }
};

class DETECTOR_EXPORT VariableRulePairOfConstructorAndAssignment final : public Rule{
public:
    VariableRulePairOfConstructorAndAssignment();
    ~VariableRulePairOfConstructorAndAssignment();
    bool detectCore(const string & code, const ErrorFile & errorFile) override;
    void resetData() override;
    bool calculateType(const string& code, const string& className, ErrorFileWithType& errorFileWithTpe);
private:
    unique_ptr<ClassDefinition> m_classDefinition;
    ErrorFileWithType m_constructor;
    ErrorFileWithType m_assignment;
};
REGISTER_CLASS(VariableRulePairOfConstructorAndAssignment)
