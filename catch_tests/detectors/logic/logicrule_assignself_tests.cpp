#include "../../catch.hpp"
#include "detectors/logic/logicrule_assignself.h"

static constexpr auto code1 = R"delimiter(
void LogicRuleAssignSelfDemo()
{
    int i;
    i = i;
}
)delimiter";

SCENARIO("LogicRuleAssignSelf", "") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                LogicRuleAssignSelf rule;
                CHECK(rule.detect(code1, "dd.h"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                LogicRuleAssignSelf rule;
                rule.resetData();
            }
        }
    }
}