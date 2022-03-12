#include "sizeofrule_withnumber.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"

SizeOfRuleWithNumber::SizeOfRuleWithNumber() : Rule("SizeOfRuleWithNumber")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        U8("对一个数字常量使用sizeof，请确认是否有意义"));
}

bool SizeOfRuleWithNumber::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (code.find("sizeof") == string::npos)
    {
        return false;
    }

    if (DetectorHelper::check(code, "sizeof\\s*\\(\\s*\\d+").empty())
    {
        return false;
    }

    storeRuleError(errorFile);
    return true;
}

void SizeOfRuleWithNumber::resetData()
{
    Rule::resetData();
    m_arrayName.clear();
}

