#include "../../doctest.h"
#include "detectors/confused/confusedrule_diffvariablewithinitandcondition.h"

SCENARIO("ConfusedRuleDiffVariableWithInitAndCondition") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                ConfusedRuleDiffVariableWithInitAndCondition rule;
                CHECK(!rule.detect(R"delimiter1(if (ret.empty())delimiter1", "dd"));
                CHECK(!rule.detect(R"delimiter1(if (auto ret1 = DetectorHelper::check(ret[1], R\"delimiter(\w+\s+\w+\s*$)delimiter\"); ret1.empty()))delimiter1", "dd"));
                CHECK(rule.detect(R"delimiter1(if (auto ret1 = DetectorHelper::check(ret[1], R\"delimiter(\w+\s+\w+\s*$)delimiter\"); ret.empty()))delimiter1", "dd"));
            }
        }
        WHEN("Mismatch condition") {
            THEN("Mismatching rule") {
                ConfusedRuleDiffVariableWithInitAndCondition rule;
                CHECK(!rule.detect("class A", "dd.h"));

            }
        }
        WHEN("just called") {
            THEN("called") {
                ConfusedRuleDiffVariableWithInitAndCondition rule;
                rule.resetData();
            }
        }
    }
}