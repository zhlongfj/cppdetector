#include "confusedrule_priority.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"

ConfusedRulePriority::ConfusedRulePriority() : Rule("ConfusedRulePriority")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        U8("令人迷惑的优先级，+优先级高于<<"));
}

bool ConfusedRulePriority::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (code.find("<<") == string::npos)
    {
        return false;
    }
    if (auto ret = DetectorHelper::check(code, "\\w+\\s*<<\\s*\\w+\\s*\\+\\s*\\w+"); !ret.empty())
    {
        //check "int iTemp = 10 << iMax + 3;"
        storeRuleError(errorFile);
        return true;
    }
    return false;
}

void ConfusedRulePriority::resetData()
{
    Rule::resetData();
}

