#include "looprule_helper.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"

bool LoopRuleHelper::findNotAutoFromFor(const string& code)
{
    if (code.find("for") == string::npos)
    {
        return false;
    }

    if (auto ret = DetectorHelper::checkFor(code); !ret.empty())
    {
        auto variableWithType = ret[1].str();  //can not remove temp variable variableWithType
        if (auto ret1 = DetectorHelper::check(variableWithType, "((.+)\\s+)*(\\w+)\\s*$"); !ret1.empty())
        {
            return ret1[2] != "auto";
        }
    }

    return false;
}

VariableInFor LoopRuleHelper::getVariablesFromFor(const string& code)
{
    if (code.find("for") == string::npos)
    {
        return { "", set<string>() };
    }

    if (auto ret = DetectorHelper::checkFor(code); !ret.empty())
    {
        auto variableWithType = ret[1].str();  //can not remove temp variable variableWithType
        if (auto ret1 = DetectorHelper::check(variableWithType, "((.+)\\s+)*(\\w+)\\s*$"); !ret1.empty())
        {
            return { ret[2], set<string>({ ret1[3], ret[2], ret[4] }) };
        }
    }
    return { "", set<string>() };
}

bool LoopRuleHelper::isValid(const string& code, string& variable)
{
    auto variablesInFor = LoopRuleHelper::getVariablesFromFor(code);
    if (!variablesInFor.second.empty())
    {
        variable = *variablesInFor.second.begin();
        return false;
    }

    if (DetectorHelper::isFunctionDefinition(code))
    {
        variable.clear();
        return false;
    }

    if (variable.empty()
        || code.find(variable) == string::npos)
    {
        return false;
    }

    return true;
}

