#include "operationrule_bitwisewithbool.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"
#include "common/filehelp.h"

OperationRuleBitwiseWithBool::OperationRuleBitwiseWithBool() : Rule("OperationRuleBitwiseWithBool")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Error, m_name,
        "Bitwise operations on bool will cause unexpected results.",
        U8("对bool进行位操作将导致非预期结果"));
}

bool OperationRuleBitwiseWithBool::detectCore(const string& code, const ErrorFile& errorFile)
{
    return false;
    if ((code.find("&") == string::npos || code.find("&&") != string::npos)
        && (code.find("|") == string::npos || code.find("||") != string::npos))
    {
        return false;
    }
    auto codeTmp = StringHelper(code).removeSpaceAndTab();
    if (auto ret = DetectorHelper::check(codeTmp, "(.+)[&|](.+);"); !ret.empty())
    {
        string left = ret[2];
        string ss = ret[1];
        if (auto ret1 = DetectorHelper::check(ss, "=(.+)"); !ret1.empty())
        {
            left = ret1[1];
        }
        if (valid(left, errorFile.path) || valid(ret[3], errorFile.path))
        {
            storeRuleError(errorFile);
            return true;
        }

        return false;
    }

    return true;
}

bool OperationRuleBitwiseWithBool::valid(const string& variableName, const string& path)
{
    if (DetectorHelper::check(variableName, "^\\w+$").empty())
    {
        //handle variableName = "memcpy(&a," from code: "memcpy(&a, &b, sizeof(b));"
        return false;
    }
    if (m_data.empty())
    {
        m_data = FileHelp().parse(path);
    }

    if (auto ret = DetectorHelper::check(m_data, getRegValue(variableName)); !ret.empty())
    {
        if (ret[1] == "bool" || !ret[3].str().empty())
        {
            return true;
        }
    }

    return false;
}

std::string OperationRuleBitwiseWithBool::getRegValue(const string& variableName)
{
    return "(\\w+)\\s+" + variableName + "\\s*(=\\s*(true|false))*";
}

void OperationRuleBitwiseWithBool::resetData()
{
    Rule::resetData();
    m_data.clear();
}

