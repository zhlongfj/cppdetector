#include "../../catch.hpp"
#include<regex>
#include "detectors/pointer/pointerrule_notcheck.h"

static constexpr auto checkFirst = R"delimiter(
void func1()
{
    if (obj != nullptr)
    {
        obj->dosth();
    }
}
void func2()
{
    obj->dosth2();
}
)delimiter";

static constexpr auto checkTernary = R"delimiter(
void func1()
{
    if (obj != nullptr)
    {
        obj->dosth();
    }
}
void func2()
{
    obj?obj->dosth2():fun();
}
)delimiter";

static constexpr auto checkLast = R"delimiter(
void Demo(C* obj)
{
    // obj先解引用，但在后面对obj进行了判空，此处解引用并不在判空保护范围以内
    obj->dosth2();
    obj->dosth();
    if (obj != nullptr) // obj判空
    {
        obj->dosth();
    }
}
)delimiter";

SCENARIO("PointerRuleNotCheck", "") {
    GIVEN("") {
        WHEN("") {
            THEN("no explicit") {
                PointerRuleNotCheck rule;
                CHECK(rule.detect(checkFirst, "dd"));
                CHECK(rule.getRuleErrors().size() == 1);
            }
            THEN("") {
                PointerRuleNotCheck rule;
                CHECK(rule.detect(checkLast, "dd"));
                CHECK(rule.getRuleErrors().size() == 2);
            }
            THEN("") {
                PointerRuleNotCheck rule;
                CHECK(!rule.detect(checkTernary, "dd"));
            }
        }
    }
}