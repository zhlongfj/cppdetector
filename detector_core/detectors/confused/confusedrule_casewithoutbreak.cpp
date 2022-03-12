#include "confusedrule_casewithoutbreak.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"

ConfusedRuleCaseWithoutBreak::ConfusedRuleCaseWithoutBreak() : Rule("ConfusedRuleCaseWithoutBreak")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        U8("令人迷惑的switch case，不是所有的case语句都有break，请确认是否遗漏"));
}

bool ConfusedRuleCaseWithoutBreak::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (code.find("switch") == string::npos
        && code.find("case") == string::npos
        && code.find("default") == string::npos
        && code.find("break") == string::npos
        && code.find("return") == string::npos)
    {
        return false;
    }

    if (code.find("switch") != string::npos)
    {
        if (!DetectorHelper::check(code, "switch\\s*\\(").empty())
        {
            m_inSwitch = true;
            m_inCase = false;
            m_switchState.push_back({ true, false });
        }
        return false;
    }

    if (code.find("default") != string::npos
        || m_inSwitch && !m_inCase && code.find("}") != string::npos)
    {
        m_inSwitch = false;
        m_inCase = false;
        if (!m_switchState.empty())
        {
            m_switchState.pop_back();
            if (!m_switchState.empty())
            {
                m_inSwitch = m_switchState.back().first;
                m_inCase = m_switchState.back().second;
            }
        }
    }

    if (!m_inSwitch)
    {
        return false;
    }

    if (!DetectorHelper::check(code, "(default\\s*:)|(case .+:)").empty())
    {
        if (m_cases.empty()
            || errorFile.line > m_cases[m_cases.size() - 1].line + 1)
        {
            m_cases.emplace_back(errorFile);
        }
        else
        {
            m_cases[m_cases.size() - 1].line += 1;
        }
    }

    if (!DetectorHelper::check(code, "(break\\s*;)|(return\\s+)").empty())
    {
        // abnormal stuation: two break or break after return
        if (!m_cases.empty())
        {
            m_cases.pop_back();
        }
    }
    return false;
}

void ConfusedRuleCaseWithoutBreak::resetData()
{
    for (const auto& item : m_cases)
    {
        storeRuleError(item);
    }
    Rule::resetData();
    m_cases.clear();
    m_switchState.clear();
    m_inSwitch = false;
    m_inCase = false;
}

