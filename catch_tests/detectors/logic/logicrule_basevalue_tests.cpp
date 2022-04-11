#include "../../catch.hpp"
#include "detectors/logic/logicrule_basevalue.h"

static constexpr auto code1 = R"delimiter(
void LogicRuleBaseValueDemo()
{
    if (1) {};
    if (0) {};
    if (true) {};
    if (false) {};
}
)delimiter";

SCENARIO("LogicRuleBaseValue", "") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                LogicRuleBaseValue rule;
                CHECK(rule.detect(code1, "dd.h"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                LogicRuleBaseValue rule;
                rule.resetData();
            }
        }
    }
}