#include "confusedrule_assignmentinassertorif.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"
#include "detectorcommon/ifdefinition.h"

ConfusedRuleAssignmentInAssertOrIf::ConfusedRuleAssignmentInAssertOrIf() : Rule("ConfusedRuleAssignmentInAssertOrIf")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Error, m_name,
        "Confusing assignment. Put the assignment statement inside an assertion statement of if statement.",
        U8("令人迷惑的赋值，将赋值语句放到断言或if中"));
}

bool ConfusedRuleAssignmentInAssertOrIf::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (auto ret = makeCondition(code, "assert"); isAssignment(ret))
    {
        storeRuleError(errorFile);
        return true;
    }

    IfDefinition ifDefinition;
    ifDefinition.inIfDefinition(code);
    if (!isAssignment(ifDefinition.condition()))
    {
        return false;
    }
    storeRuleError(errorFile);
    return true;

}

void ConfusedRuleAssignmentInAssertOrIf::resetData()
{
    Rule::resetData();
}

std::string ConfusedRuleAssignmentInAssertOrIf::makeCondition(const string& code, const string& prefix)
{
    if (code.find(prefix) == string::npos)
    {
        return "";
    }

    auto ret = DetectorHelper::checkInBracket(code, prefix);
    if (ret.empty())
    {
        return "";
    }

    return ret[1];
}

bool ConfusedRuleAssignmentInAssertOrIf::isAssignment(const string& code)
{
    return !checkOperator(code, "=").empty();
}

std::smatch ConfusedRuleAssignmentInAssertOrIf::checkOperator(const string& code, const string& arithmetic)
{
    auto tmp = "\\s*\\w+\\s*";
    return DetectorHelper::check(code, tmp + arithmetic + "\\s*\"*\\w");
}

