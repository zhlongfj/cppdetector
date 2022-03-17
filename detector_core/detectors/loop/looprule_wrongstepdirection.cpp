#include "looprule_wrongstepdirection.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"
#include "looprule_helper.h"
#include "detectorcommon/fordefinition.h"

LoopRuleWrongStepDirection::LoopRuleWrongStepDirection() : Rule("LoopRuleWrongStepDirection")
, m_forDefinition(make_unique<ForDefinition>())
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        "Please check the iteration variable in the for loop is in the opposite direction",
        U8("for循环中的迭代变量方向是否反了"));
}

bool LoopRuleWrongStepDirection::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (!m_forDefinition->isFor(code))
    {
        return false;
    }

    auto comparationSymbol = m_forDefinition->comparationSymbol();
    auto stepOperation = m_forDefinition->stepOperation();
    if (comparationSymbol.find("<") != string::npos && stepOperation == "--"
        || comparationSymbol.find(">") != string::npos && stepOperation == "++")
    {
        storeRuleError(errorFile);
        return true;
    }
    return false;
}

void LoopRuleWrongStepDirection::resetData()
{
    Rule::resetData();
}

