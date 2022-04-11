#include "looprule_outofbounds.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"
#include "looprule_helper.h"

LoopRuleOutOfBounds::LoopRuleOutOfBounds() : Rule("LoopRuleOutOfBounds")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        "The iteration variables in for loop are modified and may be out of range, resulting in an error to the loop.",
        U8("for循环中的迭代变量被修改,可能超过范围,导致循环出错"));
}

bool LoopRuleOutOfBounds::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (!LoopRuleHelper::isValid(code, m_loopVariable))
    {
        return false;
    }

    if (m_loopVariable.empty())
    {
        return false;
    }

    auto codeTmp = StringHelper(code).removeSpaceAndTab();
    auto index = codeTmp.find(m_loopVariable);
    if (index == string::npos)
    {
        return false;
    }

    auto border = "([\\+\\-]*)";
    auto regValue = border + m_loopVariable + border;
    if (auto ret = DetectorHelper::check(codeTmp, regValue); !ret.empty())
    {
        if (!ret[1].str().empty()
            || !ret[2].str().empty())
        {
            storeRuleError(errorFile);
            return true;
        }
    }

    return false;
}

void LoopRuleOutOfBounds::resetData()
{
    Rule::resetData();
    m_loopVariable.clear();
}

