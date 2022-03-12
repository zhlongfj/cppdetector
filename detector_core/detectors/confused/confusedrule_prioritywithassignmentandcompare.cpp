#include "confusedrule_prioritywithassignmentandcompare.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"
#include "detectorcommon/ifdefinition.h"

ConfusedRulePriorityWithAssignmentAndCompare::ConfusedRulePriorityWithAssignmentAndCompare() : Rule("ConfusedRulePriorityWithAssignmentAndCompare")
    , m_ifDefinition(make_unique<IfDefinition>())
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        U8("令人迷惑的优先级，比较运算符高于赋值运算符，请确认是否需要添加括号"));
}

ConfusedRulePriorityWithAssignmentAndCompare::~ConfusedRulePriorityWithAssignmentAndCompare() = default;

bool ConfusedRulePriorityWithAssignmentAndCompare::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (!m_ifDefinition->inIfDefinition(code))
    {
        return false;
    }

    auto conditionContexts = m_ifDefinition->getConditionContexts();

    for (const auto& item : conditionContexts)
    {
        if (item.operatorName != "=")
        {
            continue;
        }
        auto operand = item.operands.second;
        if (operand.find("<") == string::npos
            && operand.find(">") == string::npos)
        {
            continue;
        }
        storeRuleError(errorFile);
        return true;
    }

    return false;
}

void ConfusedRulePriorityWithAssignmentAndCompare::resetData()
{
    Rule::resetData();
    m_ifDefinition->resetData();
}

