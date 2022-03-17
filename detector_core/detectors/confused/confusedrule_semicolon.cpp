#include "confusedrule_semicolon.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"

ConfusedRuleSemicolon::ConfusedRuleSemicolon() : Rule("ConfusedRuleSemicolon")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        "Confusing. It is possibly mistyped.",
        U8("令人迷惑的;，可能是误输入的"));
}

bool ConfusedRuleSemicolon::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (code.find("if") == string::npos
        && code.find("for") == string::npos
        && code.find("while") == string::npos)
    {
        return false;
    }

    if (auto ret = DetectorHelper::check(code, "\\s+(if|for|while)\\s*\\(.*\\);[\\n\\s]*$"); !ret.empty())
    {
        //check "if (iMax > 0 && iMax != 3);"
        //"[\\n\\s]*$" is necessary to prevent a match to "for(iter = ivec.begin();iter!=ivec.end();iter++)"
        if (code.find("while") != string::npos)
        {
            //filter do while
            auto prefix = ret.prefix().str();
            if (!prefix.empty()
                && prefix[prefix.size() - 1] == '}')
            {
                return false;
            }
        }
        storeRuleError(errorFile);
        return true;
    }

    return false;
}

void ConfusedRuleSemicolon::resetData()
{
    Rule::resetData();
}

