#include "../../catch.hpp"
#include "detectors/loop/looprule_wrongstepdirection.h"

static constexpr auto code1 = R"delimiter(
void LoopRuleWrongVariableDemo(int iMax)
{
    for (int i = 0; i < iMax; --i)
    {

    }
}
)delimiter";

static constexpr auto code2 = R"delimiter(
void LoopRuleWrongVariableDemo(int iMax)
{
    for (int i = iMax - 1; i > 0; ++i)
    {

    }
}
)delimiter";

SCENARIO("LoopRuleWrongStepDirection", "") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule1") {
                LoopRuleWrongStepDirection rule;
                CHECK(rule.detect(code1, "dd"));
            }
            THEN("Matching rule2") {
                LoopRuleWrongStepDirection rule;
                CHECK(rule.detect(code2, "dd"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                LoopRuleWrongStepDirection rule;
                rule.resetData();
            }
        }
    }
}