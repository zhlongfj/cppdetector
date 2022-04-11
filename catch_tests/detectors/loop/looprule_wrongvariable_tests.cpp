#include "../../catch.hpp"
#include "detectors/loop/looprule_wrongvariable.h"

static constexpr auto code1 = R"delimiter(
void LoopRuleWrongVariableDemo(int iMax)
{
    for (int i = 0; i < iMax; ++j)
    {

    }
}
)delimiter";

SCENARIO("LoopRuleWrongVariable", "") {
    GIVEN("") {
        WHEN("Mismatch condition") {
            THEN("Mismatching rule") {
                LoopRuleWrongVariable rule;
                CHECK(rule.detect(code1, "dd"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                LoopRuleWrongVariable rule;
                rule.resetData();
            }
        }
    }
}