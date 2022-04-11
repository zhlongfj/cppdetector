#include "../../catch.hpp"
#include "detectors/confused/confusedrule_nothandlefuncreturn.h"

static constexpr auto code1 = R"delimiter(
int* DemoFunc()
{
    if (rand() > 1024)
    {
        int* p = new int;
        return p;
    }
    return nullptr;
}

void PointerRuleReturnNullDemo()
{
    int* p = DemoFunc();
    DemoFunc();
}

)delimiter";

SCENARIO("ConfusedRuleNotHandleFuncReturn", "") {
    GIVEN("") {
        WHEN("") {
            THEN("no explicit") {
                ConfusedRuleNotHandleFuncReturn rule;
                CHECK(rule.detect(code1, "dd.h"));
                CHECK(rule.getRuleErrors().size() == 1);
            }
        }
        WHEN("just called") {
            THEN("called") {
                ConfusedRuleNotHandleFuncReturn rule;
                rule.resetData();
            }
        }
    }
}