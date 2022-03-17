#include "logicrule_expressionrepetition.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"

LogicRuleExpressionRepetition::LogicRuleExpressionRepetition() : Rule("LogicRuleExpressionRepetition")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        "The logic and expression are repeated.Please make sure whether it is correct.",
        U8("逻辑与表达式重复，请确认是否正确"));
}

bool LogicRuleExpressionRepetition::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (code.find("&&") == string::npos)
    {
        return false;
    }
    auto ret = DetectorHelper::check(code, R"delimiter((\w+)\s*([>=<!]+)\s*(\w+)\s*&&\s*(\w+)\s*([>=<!]+)\s*(\w+))delimiter");
    if (ret.empty()
        || ret[2] != ret[5])
    {
        return false;
    }

    //check "if (a < 3 && a < 25)" or "if (a >= 10 && a >= 20)"
    auto operation = ret[2];
    if (operation == "!="
        || operation == "==")
    {
        if (ret[1] == ret[4]
            && ret[3] == ret[6])
        {
            storeRuleError(errorFile);
            return true;
        }
    }
    else
    {
        if (ret[1] == ret[4]
            || ret[3] == ret[6])
        {
            if (StringHelper(ret[1]).isNull() || StringHelper(ret[3]).isNull())
            {
                return false;
            }
            storeRuleError(errorFile);
            return true;
        }
    }

    return false;
}

void LogicRuleExpressionRepetition::resetData()
{
    Rule::resetData();
}

