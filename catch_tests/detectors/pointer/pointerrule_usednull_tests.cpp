#include "../../catch.hpp"
#include "detectors/pointer/pointerrule_usednull.h"

static constexpr auto content = R"delimiter(
void func()
{
    IWbemClassObject *pclsObj = nullptr;
    ULONG uReturn = 0;
    HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
    if (0 == uReturn)
    {
        break;
    }
    VARIANT vtProp;
    hr = pclsObj->Get(L"ProcessorId", 0, &vtProp, 0, 0);
}
)delimiter";

SCENARIO("PointerRuleUsedNull", "") {
    GIVEN("") {
        WHEN("") {
            THEN("no explicit") {
                PointerRuleUsedNull rule;
                CHECK(!rule.detect(content, "dd"));
            }
        }
    }
}