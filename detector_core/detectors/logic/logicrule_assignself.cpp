#include "logicrule_assignself.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"

LogicRuleAssignSelf::LogicRuleAssignSelf() : Rule("LogicRuleAssignSelf")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        "Assign a value to itself. Please make sure whether the value you entered is wrong.",
        U8("给自己赋值，请确认是否写错"));
}

bool LogicRuleAssignSelf::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (code.find("=") == string::npos
        || code.find("==") != string::npos)
    {
        return false;
    }

    auto codeTmp = StringHelper(code).removeSpaceAndTab();
    auto index = codeTmp.find("=");
    auto left = codeTmp.substr(0, index);
    auto rightStart = index + strlen("=");
    auto rightEnd = codeTmp.size() - rightStart - 1;
    auto right = codeTmp.substr(rightStart, rightEnd);
    if (left != right)
    {
        return false;
    }

    storeRuleError(errorFile);
    return true;
}

void LogicRuleAssignSelf::resetData()
{
    Rule::resetData();
}
