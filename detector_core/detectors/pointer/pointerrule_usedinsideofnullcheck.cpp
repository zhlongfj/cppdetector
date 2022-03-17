#include "pointerrule_usedinsideofnullcheck.h"
#include "pointerrule_helper.h"
#include "detectorcommon/detectorhelp.h"
#include "detectorcommon/ifdefinition.h"

PointerRuleUsedInsideOfNULLCheck::PointerRuleUsedInsideOfNULLCheck() : Rule("PointerRuleUsedInsideOfNULLCheck")
, m_ifDefinition(make_unique<IfDefinition>())
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Critical, m_name,
        "Check pointer nullability first and then dereference within the nullable scope.",
        U8("指针先判空，然后在判空作用域内解引用。"));
}

PointerRuleUsedInsideOfNULLCheck::~PointerRuleUsedInsideOfNULLCheck() = default;

bool PointerRuleUsedInsideOfNULLCheck::detectCore(const string & code, const ErrorFile & errorFile)
{
    if (DetectorHelper::isFunctionDefinition(code))
    {
        m_objName.clear();
        m_inConditions.clear();
    }

    auto tmpObjName = getObjNameFromIf(code);

    if (!tmpObjName.empty())
    {
        if (auto ret = PointerRuleHelper::getDereferenceVariable(code); !ret.empty())
        {
            storeRuleError(errorFile);
            return true;
        }

        m_objName = tmpObjName;
        m_inConditions.clear();
    }

    if (m_objName.empty())
    {
        return false;
    }

    if (auto ret = DetectorHelper::checkConstructedObject(code); !ret.empty())
    {
        if (ret[1].str() == m_objName)
        {
            m_objName.clear();
        }
    }

    bool empty = m_inConditions.empty();
    bool invalid = !PointerRuleHelper::detectDereference(code, m_objName, m_inConditions)
        || m_inConditions.empty();
    if (!empty && m_inConditions.empty())
    {
        m_objName.clear();
    }

    if (invalid)
    {
        return false;
    }

    storeRuleError(errorFile);
    return true;
}

void PointerRuleUsedInsideOfNULLCheck::resetData()
{
    Rule::resetData();
    m_objName.clear();
    m_inConditions.clear();
}

string PointerRuleUsedInsideOfNULLCheck::getObjNameFromIf(const string & code)
{
    if (m_ifDefinition->inIfDefinition(code)
        && m_ifDefinition->isEnd())
    {
        auto conditions = m_ifDefinition->getConditionContexts();
        if (!conditions.empty())
        {
            if (conditions[0].operatorName == "==")
            {
                return PointerRuleHelper::getObjNameFromPair(conditions[0].operands);
            }
            else if (conditions[0].operatorName == "!")
            {
                return conditions[0].operands.first;
            }
        }
    }
    return "";
}
