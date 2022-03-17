#include "pointerrule_useduninitialized.h"
#include "../../detectorcommon/detectorcommon.h"
#include "pointerrule_helper.h"
#include "detectorcommon/detectorhelp.h"
#include <map>

PointerRuleUsedUninitialized::PointerRuleUsedUninitialized() : PointerRuleUsedUninitializedOrNull("PointerRuleUsedUninitialized")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Critical, m_name,
        "Use an uninitialized pointer (wild pointer).",
        U8("使用未初始化的指针（野指针）。"));
}

bool PointerRuleUsedUninitialized::detectCore(const string& code, const ErrorFile& errorFile)
{
    auto objName = PointerRuleHelper::getObjNameOfUninitialized(code);
    return detectReal(code, errorFile, objName);
}

