#include "looprule_suggestauto.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"
#include "looprule_helper.h"

LoopRuleSuggestauto::LoopRuleSuggestauto() : Rule("LoopRuleSuggestauto")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Suggest, m_name,
        U8("for循环中的迭代变量建议采用auto声明"));
}

bool LoopRuleSuggestauto::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (LoopRuleHelper::findNotAutoFromFor(code))
    {
        storeRuleError(errorFile);
        return true;
    }

    return false;
}

void LoopRuleSuggestauto::resetData()
{
    Rule::resetData();
    m_loopVariable.clear();
}

