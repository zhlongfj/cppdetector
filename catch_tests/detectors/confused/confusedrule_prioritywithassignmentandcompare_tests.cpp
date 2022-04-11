#include "../../catch.hpp"
#include "detectors/confused/confusedrule_prioritywithassignmentandcompare.h"

static constexpr auto code1 = R"delimiter(
    if (auto ret = DetectorHelper::check(content, "(\\w+)\\s*->"); !ret.empty())
)delimiter";
SCENARIO("ConfusedRulePriorityWithAssignmentAndCompare", "") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                ConfusedRulePriorityWithAssignmentAndCompare rule;
                CHECK(rule.detect("if (x = a < 0)", "dd.h"));
                CHECK(!rule.detect(code1, "dd.h"));
            }
        }
        WHEN("Mismatch condition") {
            THEN("Mismatching rule") {
                ConfusedRulePriorityWithAssignmentAndCompare rule;
                CHECK(!rule.detect("if (x = a)", "dd.h"));
                CHECK(!rule.detect(code1, "dd.h"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                ConfusedRulePriorityWithAssignmentAndCompare rule;
                rule.resetData();
            }
        }
    }
}