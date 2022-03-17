#include "pointerrule_usednull.h"
#include "pointerrule_helper.h"
#include "detectorcommon/detectorhelp.h"

PointerRuleUsedNull::PointerRuleUsedNull() : PointerRuleUsedUninitializedOrNull("PointerRuleUsedNull")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Critical, m_name,
        "Use a null pointer.",
        U8("使用空指针"));
}

bool PointerRuleUsedNull::detectCore(const string& code, const ErrorFile& errorFile)
{
    auto objName = PointerRuleHelper::getObjNameOfNull(code);
    return detectReal(code, errorFile, objName);
}

