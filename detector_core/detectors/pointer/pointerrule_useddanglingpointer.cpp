#include "pointerrule_useddanglingpointer.h"
#include "../../detectorcommon/detectorcommon.h"
#include "pointerrule_helper.h"
#include "detectorcommon/detectorhelp.h"

PointerRuleUsedDanglingPointer::PointerRuleUsedDanglingPointer() : Rule("PointerRuleUsedDanglingPointer")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Critical, m_name,
        U8("使用悬垂指针"));
}

bool PointerRuleUsedDanglingPointer::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (!m_objNames.empty())
    {
        auto object = getObjectName(code);
        m_objNames.erase(object);
        if (m_objNames.find(object) != m_objNames.end())
        {
            return false;
        }
    }

    if (code.find("delete ") != string::npos) {
        //Performance optimization, filter mismatches
        auto ret = DetectorHelper::check(code, "delete\\s+(\\w+)");
        if (!ret.empty()) {
            m_objNames.insert(ret[1]);
            return false;
        }
    }

    if (DetectorHelper::isFunctionDefinition(code))
    {
        resetData();
        return false;
    }

    if (any_of(m_objNames.begin(), m_objNames.end(), [&code](const string& item)
        {return PointerRuleHelper::getDereferenceVariable(code) == item; }))
    {
        storeRuleError(errorFile);
        return true;
    }

    return false;
}

void PointerRuleUsedDanglingPointer::resetData()
{
    Rule::resetData();
    m_objNames.clear();
}

std::string PointerRuleUsedDanglingPointer::getObjectName(const string& code)
{
    auto codeTemp = StringHelper(code).removeSpaceAndTab();
    auto left = codeTemp.find("*");
    auto right = codeTemp.find("=");
    if (left != string::npos
        && right != string::npos)
    {
        return codeTemp.substr(left + 1, right - left - 1);
    }

    if (auto ret = DetectorHelper::checkConstructedObject(code); !ret.empty())
    {
        return ret[1].str();
    }

    return "";
}

