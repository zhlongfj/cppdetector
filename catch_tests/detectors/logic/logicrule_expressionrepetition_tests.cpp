#include "../../catch.hpp"
#include "detectors/logic/logicrule_expressionrepetition.h"

static constexpr auto code1 = R"delimiter(
void LogicRuleExpressionRepetitionDemo(int a)
{
    if (a < 3 && a < 25)
    {
        return;
    }

    if (a >= 10 && a >= 20)
    {
        return;
    }

    if (a != 10 && a == 20) {}
}
)delimiter";

SCENARIO("LogicExpressionRepetition", "") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule1") {
                LogicRuleExpressionRepetition rule;
                CHECK(!rule.detect("assert(parent != nullptr && pData != nullptr);", "dd"));
                CHECK(!rule.detect(" if (rc_ != SQLITE_ROW && rc_ != SQLITE_DONE)", "dd"));
                CHECK(!rule.detect(" if (rc_ == SQLITE_ROW && rc_ == SQLITE_DONE)", "dd"));

                CHECK(rule.detect(" if (rc_ != SQLITE_ROW && rc_ != SQLITE_ROW)", "dd"));
                CHECK(rule.detect(" if (rc_ == SQLITE_ROW && rc_ == SQLITE_ROW)", "dd"));
                CHECK(rule.detect("if (a >= 10 && a >= 20)", "dd"));
            }
            THEN("Matching rule2") {
                LogicRuleExpressionRepetition rule;
                CHECK(rule.detect(code1, "dd"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                LogicRuleExpressionRepetition rule;
                rule.resetData();
            }
        }
    }
}