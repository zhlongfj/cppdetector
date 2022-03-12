#include "pointerrule_ifnulldefect.h"
#include "detectorcommon/detectorhelp.h"
#include "../../detectorcommon/detectorcommon.h"
#include "pointerrule_helper.h"

PointerRuleIfNullDefect::PointerRuleIfNullDefect() : Rule("PointerRuleIfNullDefect")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Critical, m_name,
        U8("表达式判空并逻辑与对指针进行解引用"));
}

bool PointerRuleIfNullDefect::detectCore(const string& code, const ErrorFile& errorFile)
{
    auto ret = DetectorHelper::getValueFromOperator(code, "==");
    if (!ret.first.empty()
        && PointerRuleHelper::existNull(code))
    {
        m_objName = PointerRuleHelper::getObjNameFromPair(ret);
        if (code.find("&&") == string::npos)
        {
            return false;
        }

        if (PointerRuleHelper::getDereferenceVariable(code) != m_objName)
        {
            m_hasAnd = true;
            return false;
        }

        storeRuleError(errorFile);
        resetData();
        return true;
    }

    if (!m_objName.empty()
        && PointerRuleHelper::getDereferenceVariable(code) == m_objName)
    {
        if (m_hasAnd || code.find("&&") != string::npos)
        {
            storeRuleError(errorFile);
            resetData();
            return true;
        }
    }

    resetData();
    return false;
}

void PointerRuleIfNullDefect::resetData()
{
    Rule::resetData();
    m_objName.clear();
    m_hasAnd = false;
}

