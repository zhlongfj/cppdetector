#include "looprule_wrongvariable.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"
#include "looprule_helper.h"

LoopRuleWrongVariable::LoopRuleWrongVariable() : Rule("LoopRuleWrongVariable")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        U8("for循环迭代变量不一致"));
}

bool LoopRuleWrongVariable::detectCore(const string& code, const ErrorFile& errorFile)
{
    auto variablesInFor = LoopRuleHelper::getVariablesFromFor(code);
    if (variablesInFor.second.size() > 1)
    {
        storeRuleError(errorFile);
        return true;
    }
    return false;
}

void LoopRuleWrongVariable::resetData()
{
    Rule::resetData();
}

