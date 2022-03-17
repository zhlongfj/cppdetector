#include "confusedrule_constructor.h"
#include "../../common/stringhelper.h"
#include "detectorcommon/detectorhelp.h"

ConfusedRuleConstructor::ConfusedRuleConstructor() : Rule("ConfusedRuleConstructor")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        "Confusing constructor. A non-explicit constructor with a single parameter may lead to implicit conversion and cause ambiguity.",
        U8("令人迷惑的构造函数，带有1个参数的非显式构造函数可能导致隐性转换造成二义性"));
}

bool ConfusedRuleConstructor::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (code.find("class ") != string::npos)
    {
        if (auto ret = DetectorHelper::check(code, "class\\s+(\\w+)"); !ret.empty())
        {
            m_className = ret[1];
        }
        return false;
    }

    auto regValue = "^\\s*(\\w+ )*" + m_className + "\\s*\\(\\w+";
    auto ret = DetectorHelper::check(code, regValue);
    if (ret.empty())
    {
        return false;
    }

    if (ret[0].str().find("explicit") != string::npos)
    {
        return false;
    }

    if (code.find("(const " + m_className) != string::npos)
    {
        //A(const A & s)
        return false;
    }
    auto suffix = ret.suffix().str();
    auto indexOfRightParentheses = StringHelper(suffix).removeSpaceAndTab().find(')');
    if (indexOfRightParentheses != string::npos
        && indexOfRightParentheses > 0)
    {
        auto parameters = suffix.substr(0, indexOfRightParentheses);
        auto indexOfComma = parameters.rfind(',');
        if (indexOfComma != string::npos)
        {
            auto ret1 = DetectorHelper::check(parameters, "<.+>");
            if (ret1.empty()
                || ret1.suffix().str().find('.') != string::npos)
            {
                return false;
            }
        }
        storeRuleError(errorFile);
        return true;
    }

    return false;
}

void ConfusedRuleConstructor::resetData()
{
    Rule::resetData();
    m_className.clear();
}

