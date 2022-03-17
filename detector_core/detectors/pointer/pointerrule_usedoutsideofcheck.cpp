#include "pointerrule_usedoutsideofcheck.h"
#include "pointerrule_helper.h"

PointerRuleUsedOutsideOfCheck::PointerRuleUsedOutsideOfCheck() : Rule("PointerRuleUsedOutsideOfCheck")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Critical, m_name,
        "Check pointer nullability first and then dereference outside the nullable scope. "\
        "Because pointer nullability check implies that the pointer may be null in the current context, "\
        "it is recommended that nullability check protection be added to pointers that are not in the nullable scope.",
        U8("指针先判空，然后在判空作用域外解引用，因为指针判空暗示当前上下文该指针可能为空，因此建议对没有在判空作用域的指针添加判空保护。"));
}

bool PointerRuleUsedOutsideOfCheck::detectCore(const string& code, const ErrorFile& errorFile)
{
    auto tmpObjName = PointerRuleHelper::getObjNameFromIfNotEqual(code);
    if (!tmpObjName.empty())
    {
        m_objName = tmpObjName;
        m_inConditions.clear();
    }

    if (m_objName.empty())
    {
        return false;
    }

    if (auto ret = DetectorHelper::checkConstructedObject(code); !ret.empty())
    {
        if (ret[1] == m_objName)
        {
            resetData();
            return false;
        }
    }
    if (!PointerRuleHelper::detectDereference(code, m_objName, m_inConditions)
        || !m_inConditions.empty())
    {
        if (!m_inConditions.empty())
        {
            m_findBrace = true;
        }
        return false;
    }

    if (!m_findBrace)
    {
        //The conditional statement does not use braces
        return false;
    }
    storeRuleError(errorFile);
    return true;
}

void PointerRuleUsedOutsideOfCheck::resetData()
{
    Rule::resetData();
    m_objName.clear();
    m_inConditions.clear();
    m_findBrace = false;
}

