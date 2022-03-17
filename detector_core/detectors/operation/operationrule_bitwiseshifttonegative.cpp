#include "operationrule_bitwiseshifttonegative.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"

OperationRuleBitwiseShiftToNegative::OperationRuleBitwiseShiftToNegative() : Rule("OperationRuleBitwiseShiftToNegative")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Critical, m_name,
        "Shifting negative numbers will lead to unexpected results.",
        U8("对负数进行位移将导致非预期结果"));
}

bool OperationRuleBitwiseShiftToNegative::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (code.find("<<") == string::npos
        && code.find(">>") == string::npos)
    {
        return false;
    }

    if (auto ret = DetectorHelper::check(code, "\\s*(.+)\\s*(>>|<<)\\s*(.+)"); !ret.empty())
    {
        if (checkMinus(ret[1].str())
            || checkMinus(ret[3].str()))
        {
            storeRuleError(errorFile);
            return true;
        }
    }

    return false;
}

void OperationRuleBitwiseShiftToNegative::resetData()
{
    Rule::resetData();
}

bool OperationRuleBitwiseShiftToNegative::checkMinus(const string& content)
{
    if (content.find("\\\"") != string::npos
        || content.find("->") != string::npos)
    {
        return false;
    }

    auto index = content.find("-");
    if (index == string::npos)
    {
        return false;
    }

    return !DetectorHelper::check(content, "-\\d+").empty();
}

