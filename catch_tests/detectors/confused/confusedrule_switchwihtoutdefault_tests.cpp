#include "../../catch.hpp"
#include<regex>
#include "detectors/confused/confusedrule_switchwihtoutdefault.h"

static constexpr auto code1 = R"delimiter(
void ConfusedRuleStatementOutsideOfCaseDemo(int b)
{
    int c = 0;
    switch (b)
    {
    case 2:
        c = 2;
        break;
    }
    int a = 6;
}
)delimiter";

static constexpr auto code2 = R"delimiter(
void ConfusedRuleStatementOutsideOfCaseDemo(int b)
{
    int c = 0;
    switch (b)
    {
    case 2:
        c = 2;
        break;
    default:
        c = 3;
        break;
    }
    int a = 6;
}
)delimiter";

SCENARIO("ConfusedRuleSwitchWithoutDefault", "") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                ConfusedRuleSwitchWithoutDefault rule;
                CHECK(!rule.detect(code1, "dd.h"));
                rule.resetData();
                CHECK(rule.getRuleErrors().size() == 1);
            }
        }
        WHEN("Mismatch condition") {
            THEN("Mismatching rule") {
                ConfusedRuleSwitchWithoutDefault rule;
                CHECK(!rule.detect(code2, "dd.h"));
                rule.resetData();
                CHECK(rule.getRuleErrors().empty());
            }
        }
    }
}