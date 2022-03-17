#include "confusedrule_returnbool.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"

ConfusedRuleReturnBool::ConfusedRuleReturnBool() : Rule("ConfusedRuleReturnBool")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Error, m_name,
        "Confusing function return value. The return value type is bool, but the return statement is a different type.",
        U8("令人迷惑的函数返回值，返回值类型是bool，但是return语句是其他类型"));
}

bool ConfusedRuleReturnBool::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (auto ret = DetectorHelper::getReturnTypeOfFunctionDefinition(code); !ret.empty())
    {
        m_returnTypeIsBool = ret == "bool";
        return false;
    }

    if (m_returnTypeIsBool
        && !DetectorHelper::check(code, "return\\s*\\d+\\s*;").empty())
    {
        storeRuleError(errorFile);
        return true;
    }

    return false;
}

void ConfusedRuleReturnBool::resetData()
{
    Rule::resetData();
    m_returnTypeIsBool = false;
}

