#include "memleakrule_mallocfree.h"
#include "detectorcommon/detectorhelp.h"

MemLeakRuleMallocFree::MemLeakRuleMallocFree() : Rule("MemLeakRuleMallocFree")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Suggest, m_name,
        "malloc/free are not recommended. new/delete are recommended.",
        U8("不建议使用malloc/free，请使用new/delete替代"));
}

bool MemLeakRuleMallocFree::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (!StringHelper(code).findCode("malloc")
        && !StringHelper(code).findCode("free"))
    {
        return false;
    }

    if (StringHelper(code).findCode("realloc"))
    {
        return false;
    }

    storeRuleError(errorFile);
    return true;
}

void MemLeakRuleMallocFree::resetData()
{
    Rule::resetData();
}

