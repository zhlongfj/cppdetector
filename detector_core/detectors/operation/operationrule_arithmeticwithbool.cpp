#include "operationrule_arithmeticwithbool.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"

OperationRuleArithmeticWithBool::OperationRuleArithmeticWithBool() : Rule("OperationRuleArithmeticWithBool")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Error, m_name,
        U8("对bool进行四则运算可能会导致不可预知的结果"));
}

bool OperationRuleArithmeticWithBool::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (code.find("bool") != string::npos)
    {
        if (code.find("template") != string::npos
            || DetectorHelper::isFunctionDefinition(code))
        {
            return false;
        }
        if (auto ret = DetectorHelper::check(code, "bool\\s*(\\w+)"); !ret.empty())
        {
            m_varNames.insert(ret[1]);
            return false;
        }
    }

    if (m_varNames.empty())
    {
        return false;
    }

    if (auto ret = DetectorHelper::check(code, "(\\w+)\\s*[+\\-/%]\\s*(\\w+)\\s*[=<>,;\\)\\]\\}]"); !ret.empty())
    {
        //do not check "*"
        if (ret[1].str() == "return"
            || DetectorHelper::isFunctionDefinition(code))
        {
            return false;
        }
        //\* must be \\\\* in the []
        if (any_of(m_varNames.begin(), m_varNames.end(), [&ret](const auto& item) {
            return ret[1].str() == item || ret[2].str() == item; }))
        {
            storeRuleError(errorFile);
            return true;
        }
    }
    return false;
}

void OperationRuleArithmeticWithBool::resetData()
{
    Rule::resetData();
    m_varNames.clear();
}

