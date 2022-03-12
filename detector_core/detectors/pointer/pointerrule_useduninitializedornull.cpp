#include "pointerrule_useduninitializedornull.h"
#include "../../detectorcommon/detectorcommon.h"
#include "pointerrule_helper.h"
#include <map>
#include "detectorcommon/detectorhelp.h"

bool PointerRuleUsedUninitializedOrNull::detectReal(const string& code, const ErrorFile& errorFile, const string& objName)
{
    if (objName.empty())
    {
        if (m_objNames.empty())
        {
            return false;
        }
    }

    if (!objName.empty()
        && m_objNames.find(objName) == m_objNames.end())
    {
        m_objNames.insert({ objName, true });
        return false;
    }

    if (DetectorHelper::isFunctionDefinition(code))
    {
        resetData();
        return false;
    }

    auto value = DetectorHelper::getValueFromOperator(code, "=");
    if (!value.first.empty()
        && m_objNames.find(value.first) != m_objNames.end())
    {
        if (!PointerRuleHelper::isNull(value.second))
        {
            m_objNames[value.first] = false;
            return false;
        }
    }

    for (const auto& item : m_objNames)
    {
        if (code.find(item.first) != string::npos
            && !DetectorHelper::check(code, "&\\s*" + item.first).empty())
        {
            m_objNames[item.first] = false;
            return false;
        }
    }

    if (any_of(m_objNames.begin(), m_objNames.end(), [&code](const auto& item)
        {return PointerRuleHelper::getDereferenceVariable(code) == item.first && item.second; }))
    {
        storeRuleError(errorFile);
        return true;
    }

    return false;
}

void PointerRuleUsedUninitializedOrNull::resetData()
{
    Rule::resetData();
    m_objNames.clear();
}

