#include "confusedrule_statementOutsideOfcase.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"

ConfusedRuleStatementOutsideOfCase::ConfusedRuleStatementOutsideOfCase() : Rule("ConfusedRuleStatementOutsideOfCase")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        "Confusing switch case. All the codes in switch should be based on a case condition.",
        U8("令人迷惑的switch case，switch中的代码都应该位于某个case条件中"));
}

bool ConfusedRuleStatementOutsideOfCase::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (StringHelper(code).findCode("switch"))
    {
        m_inSwitch = true;
        m_inCase = false;
        return false;
    }

    if (code.find("default") != string::npos
        || m_inSwitch && !m_inCase && code.find("}") != string::npos)
    {
        m_inSwitch = false;
        m_inCase = false;
        return false;
    }

    if (!m_inSwitch)
    {
        return false;
    }

    if (!DetectorHelper::check(code, "case .+:").empty())
    {
        m_inCase = true;
        return false;
    }

    if (code.find("break") != string::npos)
    {
        m_inCase = false;
        return false;
    }

    if (m_inSwitch && !m_inCase)
    {
        if (!DetectorHelper::check(code, "^\\s*\\w+").empty())
        {
            storeRuleError(errorFile);
            return true;
        }
    }

    return false;
}

void ConfusedRuleStatementOutsideOfCase::resetData()
{
    Rule::resetData();
    m_inSwitch = false;
    m_inCase = false;
}

