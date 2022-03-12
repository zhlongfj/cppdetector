#include "operationrule_module.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"

OperationRuleModule::OperationRuleModule() : Rule("OperationRuleModule")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Error, m_name,
        U8("取模的判断条件总是为真或为假"));
}

bool OperationRuleModule::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (code.find("%") == string::npos
        || code.find("\"") != string::npos)
    {
        return false;
    }

    if (auto ret = DetectorHelper::check(code, "if\\s*\\((.+)\\s*==\\s*(\\w+)"); !ret.empty())
    {
        if (invalid(ret[1], ret[2]))
        {
            storeRuleError(errorFile);
            return true;
        }
    }
    return false;
}

void OperationRuleModule::resetData()
{
    Rule::resetData();
}

bool OperationRuleModule::invalid(const string& str1, const string& str2)
{
    string reference = str2;
    auto module = getModule(str1);
    if (module == 0)
    {
        reference = str1;
        module = getModule(str2);
    }

    return StringHelper(reference).isDigit() && stoi(reference) >= module;
}

int OperationRuleModule::getModule(const string& str)
{
    if (str.find("%") != string::npos)
    {
        if (auto ret = DetectorHelper::check(str, "(.+)\\s*%\\s*(\\d+)"); !ret.empty())
        {
            //check "count++ % 20 == 0"
            return stoi(ret[2]);
        }
    }
    return 0;
}

