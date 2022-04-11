#include "../../catch.hpp"
#include "detectors/confused/confusedrule_assignmentinassertorif.h"

static constexpr auto code1 = R"delimiter(
void ConfusedRulePriorityWithAssignmentAndCompareDemo()
{
    int x = 3;
    if (x = 4 > 3)
    {
    }
}
)delimiter";

static constexpr auto code2 = R"delimiter(
void ConfusedRuleAssignmentInAssertDemo()
{
    int i = 0;
    assert(i = 5);
    assert(i == 5);
}
)delimiter";

static constexpr auto code3 = R"delimiter(
void ConfusedRulePriorityWithAssignmentAndCompareDemo()
{
    if (auto ret = DetectorHelper::check(code, "\\w+\\s+(\\w+)\\[(\\w+)\\]"); !ret.empty())
    {
    }
}
)delimiter";

SCENARIO("ConfusedRuleAssignmentInAssertOrIf", "") {
    GIVEN("") {
        WHEN("Assignment in the if statement") {
            THEN("Matching rule") {
                ConfusedRuleAssignmentInAssertOrIf rule;
                CHECK(rule.detect(code1, "dd.h"));
            }
        }
        WHEN("Assignment in the assert statement") {
            THEN("Matching rule") {
                ConfusedRuleAssignmentInAssertOrIf rule;
                CHECK(rule.detect(code2, "dd.h"));
                CHECK(rule.getRuleErrors().size() == 1);
            }
        }
        WHEN("Assignment in the if statement with C++17") {
            THEN("Misatching rule") {
                ConfusedRuleAssignmentInAssertOrIf rule;
                CHECK(!rule.detect(code3, "dd.h"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                ConfusedRuleAssignmentInAssertOrIf rule;
                rule.resetData();
            }
        }
    }
}