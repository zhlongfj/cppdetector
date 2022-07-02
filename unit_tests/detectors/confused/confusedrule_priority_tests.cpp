#include "../../doctest.h"
#include "detectors/confused/confusedrule_priority.h"

static constexpr auto code1 = R"delimiter(
void ConfusedRulePriorityDemo(int iMax)
{
    int iTemp = 10 << iMax + 3;
}
)delimiter";

SCENARIO("ConfusedRulePriority") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                ConfusedRulePriority rule;
                CHECK(rule.detect(code1, "dd.h"));
            }
        }
        WHEN("Mismatch condition") {
            THEN("Mismatching rule") {
                ConfusedRulePriority rule;
                CHECK(!rule.detect("int iTemp = 10 << iMax;", "dd.h"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                ConfusedRulePriority rule;
                rule.resetData();
            }
        }
    }
}