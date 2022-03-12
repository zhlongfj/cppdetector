#include "pointerrule_helper.h"
#include "detectorcommon/detectorhelp.h"
#include "common/stringhelper.h"

std::string PointerRuleHelper::getObjNameOfNull(const string& content)
{
    if (content.find("=") == string::npos
        || content.find("nullptr") == string::npos && content.find("NULL") == string::npos)
    {
        return "";
    }
    auto ret = DetectorHelper::check(content, R"delimiter((\w+)\s*=\s*nullptr|NULL)delimiter");
    if (ret.empty())
    {
        return "";
    }

    return ret[1];
}

std::string PointerRuleHelper::getObjNameOfUninitialized(const string& content)
{
    if (content.find("*") == string::npos
        || content.find(";") == string::npos)
    {
        //Performance optimization, filter mismatches
        return "";
    }
    auto ret = DetectorHelper::check(content, R"delimiter(^\s*(\w+)\s*\*\s*(\w+)\s*;)delimiter");
    if (ret.empty() || ret[1].str() == "return")
    {
        return "";
    }

    return ret[2];
}

std::string PointerRuleHelper::getDereferenceVariable(const string& content)
{
    auto ret1 = content.find("->");
    auto ret2 = content.find("*");

    if (ret1 == string::npos && ret2 == string::npos)
    {
        return "";
    }

    if (ret1 != string::npos)
    {
        if (auto ret = DetectorHelper::check(content, "(\\w+)\\s*->"); !ret.empty())
        {
            return ret[1];
        }
    }

    if (ret2 != string::npos)
    {
        if (auto ret = DetectorHelper::check(content, "\\s*\\*\\s*(\\w+)"); !ret.empty())
        {
            auto prefix = ret.prefix();
            if (DetectorHelper::check(prefix, "\\w+$").empty())
            {
                return ret[1];
            }
        }
    }

    return "";
}

std::pair<std::string, std::string> PointerRuleHelper::getObjNamePairFromIfNotEqual(const string& content)
{
    return getObjNamePairFromIf(content, "!=");
}

std::string PointerRuleHelper::getObjNameFromIfNotEqual(const string& content)
{
    return getObjNameFromPair(getObjNamePairFromIfNotEqual(content));
}

std::string PointerRuleHelper::getObjNameFromIfEqual(const string& content)
{
    if (content.find("if") == string::npos)
    {
        return "";
    }

    auto ret = getObjNameFromPair(getObjNamePairFromIfEqual(content));
    if (!ret.empty())
    {
        return ret;
    }

    return "";
}

std::pair<std::string, std::string> PointerRuleHelper::getObjNamePairFromIfEqual(const string& content)
{
    return getObjNamePairFromIf(content, "==");
}

bool PointerRuleHelper::isNull(const string& content)
{
    return content == "NULL" || content == "nullptr";
}

bool PointerRuleHelper::existNull(const string& content)
{
    return content.find("NULL") != string::npos || content.find("nullptr") != string::npos;
}

bool PointerRuleHelper::detectDereference(const string& content, const string& objName, vector<bool>& inConditions)
{
    auto doubleQuote = content.find("\"");
    auto left = content.find("{");
    if (left != string::npos
        && (doubleQuote == string::npos || left < doubleQuote))
    {
        inConditions.push_back(true);
    }

    auto right = content.rfind("}");
    doubleQuote = content.rfind("\"");
    if (right != string::npos
        && (doubleQuote == string::npos || right > doubleQuote))
    {
        if (!inConditions.empty())
        {
            inConditions.pop_back();
        }
        return false;
    }
    return getDereferenceVariable(content) == objName;
}

std::string PointerRuleHelper::getObjNameFromPair(const pair<string, string>& names)
{
    if (names.first.empty()
        || !isNull(names.first)
        && !isNull(names.second))
    {
        return "";
    }

    return isNull(names.first) ? names.second : names.first;
}

std::vector<std::string> PointerRuleHelper::getPointerFromIf(const string& content)
{
    auto ret = DetectorHelper::checkIf(content);
    if (ret.empty())
    {
        return {};
    }

    auto condition = StringHelper(ret[1]).removeSpaceAndTab();
    if (condition.find("&&") == string::npos
        && condition.find("||") == string::npos)
    {
        return { getPointerFromCondition(condition) };
    }

    auto ret1 = DetectorHelper::check(condition, "(.+)(&&|\\|\\|)(.+)");
    if (ret1.empty())
    {
        return {};
    }

    vector<string> objNames;
    if (auto objName = getPointerFromCondition(ret1[1]); !objName.empty())
    {
        objNames.push_back(objName);
    }

    if (auto objName = getPointerFromCondition(ret1[3]); !objName.empty())
    {
        objNames.push_back(objName);
    }

    return objNames;
}

std::string PointerRuleHelper::getPointerFromCondition(const string& condition)
{
    if (condition.find("(") != string::npos)
    {
        if (auto ret = DetectorHelper::check(condition, "\\((\\w+)\\)"); !ret.empty())
        {
            return ret[1];
        }
        return "";
    }

    if (auto indexOfEqual = condition.find("=="); indexOfEqual != string::npos)
    {
        auto variables = StringHelper(condition).split("==");
        return PointerRuleHelper::getObjNameFromPair({ variables[0], variables[1] });
    }
    else if (auto indexOfUnequal = condition.find("!="); indexOfUnequal != string::npos)
    {
        auto variables = StringHelper(condition).split("!=");
        return PointerRuleHelper::getObjNameFromPair({ variables[0], variables[1] });
    }
    else if (auto indexOfNegation = condition.find("!"); indexOfNegation != string::npos)
    {
        return condition.substr(indexOfNegation + 1);
    }

    return condition;
}

std::pair<std::string, std::string> PointerRuleHelper::getObjNamePairFromIf(const string& content, const string& comparisonOperator)
{
    if (content.find("if") == string::npos)
    {
        //Performance optimization, filter mismatches
        return { "","" };
    }
    auto ret = DetectorHelper::check(content, "if\\s*\\((\\w+)\\s*" + comparisonOperator + "\\s*(\\w+)\\)");
    if (ret.empty())
    {
        return { "", "" };
    }
    return { ret[1], ret[2] };
}

