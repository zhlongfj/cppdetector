#include "pointerrule_checkafternew.h"
#include "detectorcommon/detectorhelp.h"
#include "pointerrule_helper.h"

PointerRuleCheckAfterNew::PointerRuleCheckAfterNew() : Rule("PointerRuleCheckAfterNew")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Error, m_name,
        "After C++03, new failures will throw an exception instead of returning NULL. There is no need to check whether the value is null.",
        U8("C++03以后，new失败会抛出异常而不是返回NULL，没有必要进行判空。"));
}

bool PointerRuleCheckAfterNew::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (code.find("new ") == string::npos
        && code.find("if") == string::npos)
    {
        return false;
    }

    if (auto ret = DetectorHelper::checkConstructedObject(code); !ret.empty())
    {
        m_pointerNameFromNew = ret[1];
        return false;
    }

    if (m_pointerNameFromNew.empty())
    {
        return false;
    }

    auto ret = PointerRuleHelper::getObjNameFromPair(PointerRuleHelper::getObjNamePairFromIfEqual(code));
    auto pointerNameFromNew = m_pointerNameFromNew;
    m_pointerNameFromNew.clear();
    if (pointerNameFromNew != ret)
    {
        return false;
    }

    storeRuleError(errorFile);
    return true;
}

void PointerRuleCheckAfterNew::resetData()
{
    Rule::resetData();
    m_pointerNameFromNew.clear();
}

