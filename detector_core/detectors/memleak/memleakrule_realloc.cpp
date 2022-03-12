#include "memleakrule_realloc.h"
#include "detectorcommon/detectorhelp.h"

MemLeakRuleRealloc::MemLeakRuleRealloc() : Rule("MemLeakRuleRealloc")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        U8("realloc年轻人把握不住，让基础库实现者来把握"));
}

bool MemLeakRuleRealloc::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (!StringHelper(code).findCode("realloc"))
    {
        return false;
    }

    storeRuleError(errorFile);
    return true;
}

void MemLeakRuleRealloc::resetData()
{
    Rule::resetData();
}

