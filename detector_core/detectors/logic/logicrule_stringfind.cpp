#include "logicrule_stringfind.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"

LogicRuleStringFind::LogicRuleStringFind() : Rule("LogicRuleStringFind")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Error, m_name,
        U8("std::string的find返回值应该与string::npos比较，且只能用== 或 !=，请确认是否误用"));
}

bool LogicRuleStringFind::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (!StringHelper(code).findCode("find")
        || !StringHelper(code).findCode("if"))
    {
        return false;
    }

    if (auto ret = DetectorHelper::checkIf(code); !ret.empty())
    {
        if (!checkValid(ret[1].str()))
        {
            //check "if (0 <= str.find(search))"
            storeRuleError(errorFile);
            return true;
        }
    }

return false;
}

void LogicRuleStringFind::resetData()
{
    Rule::resetData();
}

bool LogicRuleStringFind::checkValid(const string& code)
{
    auto codeTmp = StringHelper(code).removeSpaceAndTab();
    if (auto ret1 = DetectorHelper::check(codeTmp, "[><=!]="); !ret1.empty())
    {
        auto operation = ret1[0].str();
        if (operation == "=="
            || operation == "!=")
        {
            auto prefix = ret1.prefix().str();
            auto suffix = ret1.suffix().str();
            if (StringHelper(prefix).findCode("npos")
                || StringHelper(prefix).findCode("npos"))
            {
                return true;
            }
        }
    }

    return false;
}

