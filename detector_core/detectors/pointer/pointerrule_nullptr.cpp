#include "pointerrule_nullptr.h"
#include "detectorcommon/detectorhelp.h"

PointerRuleNullptr::PointerRuleNullptr() : Rule("PointerRuleNullptr")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Suggest, m_name,
        "NULL will cause the overloading in C++ to be out of order: void foo(char*);void foo(int);",
        U8("NULL将导致 C++ 中重载特性发生混乱：void foo(char*);void foo(int);"));
}

bool PointerRuleNullptr::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (!StringHelper(code).findCode("NULL"))
    {
        return false;
    }

    storeRuleError(errorFile);
    return true;
}

