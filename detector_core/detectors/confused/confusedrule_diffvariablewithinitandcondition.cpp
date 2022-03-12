#include "confusedrule_diffvariablewithinitandcondition.h"
#include "detectorcommon/detectorhelp.h"

ConfusedRuleDiffVariableWithInitAndCondition::ConfusedRuleDiffVariableWithInitAndCondition() 
    : Rule("ConfusedRuleDiffVariableWithInitAndCondition")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        U8("在判断条件中，初始化的变量与比较变量不一致，请确认是否正确"));
}

bool ConfusedRuleDiffVariableWithInitAndCondition::detectCore(const string& code, const ErrorFile& errorFile)
{
    StringHelper helper(code);
    if (!helper.findCode("if")
        && !helper.findCode(";"))
    {
        return false;
    }

    if (auto ret = DetectorHelper::check(code, R"delimiter((\w+)\s*=.+;(.+)\)$)delimiter"); !ret.empty())
    {
        if (!StringHelper(ret[2]).findCode(ret[1]))
        {
            storeRuleError(errorFile);
            return true;
        }
    }

    return false;
}

void ConfusedRuleDiffVariableWithInitAndCondition::resetData()
{
    Rule::resetData();
}

