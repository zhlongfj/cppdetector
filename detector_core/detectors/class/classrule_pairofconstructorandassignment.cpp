#include "detectorcommon/detectorhelp.h"
#include "detectorcommon/classdefinition.h"
#include "classrule_pairofconstructorandassignment.h"

VariableRulePairOfConstructorAndAssignment::VariableRulePairOfConstructorAndAssignment() : Rule("VariableRulePairOfConstructorAndAssignment")
    , m_classDefinition(make_unique<ClassDefinition>())
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        U8("拷贝构造函数/赋值运算符或者移动构造函数/移动赋值运算符需要成对出现"));
}

VariableRulePairOfConstructorAndAssignment::~VariableRulePairOfConstructorAndAssignment() = default;

bool VariableRulePairOfConstructorAndAssignment::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (m_classDefinition->inClassDefinition(code))
    {
        if (auto ret = m_classDefinition->isConstructor(code); ret.first)
        {
            if (calculateType(code, ret.second, m_constructor))
            {
                m_constructor.errorFile = errorFile;
            }
        }

        if (auto ret = m_classDefinition->isAssignment(code); ret.first)
        {
            if (calculateType(code, ret.second, m_assignment))
            {
                m_assignment.errorFile = errorFile;
            }
        }
        return false;
    }
    else
    {
        if (m_constructor.isCopy != m_assignment.isCopy)
        {
            storeRuleError(m_constructor.isCopy ? m_constructor.errorFile : m_assignment.errorFile);
        }

        if (m_constructor.isMove != m_assignment.isMove)
        {
            storeRuleError(m_constructor.isMove != 0 ? m_constructor.errorFile : m_assignment.errorFile);
        }

        m_constructor.resetData();
        m_assignment.resetData();
        return true;
    }
}

void VariableRulePairOfConstructorAndAssignment::resetData()
{
    Rule::resetData();
    m_classDefinition->resetData();
    m_constructor.resetData();
    m_assignment.resetData();
}

bool VariableRulePairOfConstructorAndAssignment::calculateType(const string& code,
    const string& className, ErrorFileWithType& errorFileWithTpe)
{
    auto count = m_classDefinition->getReferenceCount(code, className);
    if (count == 0)
    {
        return false;
    }

    if (count == 1)
    {
        errorFileWithTpe.isCopy = true;
    }
    else if (count == 2)
    {
        errorFileWithTpe.isMove = true;
    }
    return true;
}
