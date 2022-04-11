#include "../../catch.hpp"
#include "detectors/logic/logicrule_basevalue.h"

static constexpr auto code1 = R"delimiter(
void LogicRuleIncorrectOperationDemo()
{
    if ((a != 1) || (a != 3)) {}
    if ((a == 1) && (a == 3)) {}
}
)delimiter";

SCENARIO("LogicRuleIncorrectOperation", "") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                LogicRuleBaseValue rule;
                CHECK(rule.detect("if (1)", "dd.h"));
                CHECK(rule.detect("if (0)", "dd.h"));
                CHECK(rule.detect("if (true)", "dd.h"));
                CHECK(rule.detect("if (false)", "dd.h"));
            }
            THEN("Matching rule") {
                LogicRuleBaseValue rule;
                //todo
                //CHECK(rule.detect(code1, "dd.h"));
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