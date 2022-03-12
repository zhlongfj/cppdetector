#include "confusedrule_switchwihtoutdefault.h"
#include "detectorcommon/detectorhelp.h"

ConfusedRuleSwitchWithoutDefault::ConfusedRuleSwitchWithoutDefault() : Rule("ConfusedRuleSwitchWithoutDefault")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        U8("令人迷惑的switch，缺少default，可能遗漏场景"));
}

bool ConfusedRuleSwitchWithoutDefault::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (code.find("switch ") == string::npos
        && code.find("default:") == string::npos
        && code.find("}") == string::npos)
    {
        return false;
    }

    auto index = code.find("switch ");
    if (index != string::npos)
    {
        if (index > 0 && index < code.size())
        {
            if (code.find("\"") != code.rfind("\""))
            {
                return false;
            }
        }
        m_inSwitch = true;
        m_errorFiles.emplace_back(errorFile);
        return false;
    }

    if (code.find("default:") != string::npos)
    {
        if (!m_errorFiles.empty())
        {
            m_errorFiles.pop_back();
        }
        return false;
    }

    return false;
}

void ConfusedRuleSwitchWithoutDefault::resetData()
{
    for (const auto& item : m_errorFiles)
    {
        storeRuleError(item);
    }
    Rule::resetData();
    m_errorFiles.clear();
}

