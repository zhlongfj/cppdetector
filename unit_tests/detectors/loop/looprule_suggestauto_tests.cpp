#include "../../doctest.h"
#include "detectors/loop/looprule_suggestauto.h"

SCENARIO("LoopRuleSuggestauto") {
    GIVEN("") {
        WHEN("Mismatch condition") {
            THEN("Mismatching rule") {
                LoopRuleSuggestauto rule;
                CHECK(rule.detect("	for (int i = 64; i < len; i += 64) {", "dd"));
            }
        }
        WHEN("Mismatch condition") {
            THEN("Mismatching rule") {
                LoopRuleSuggestauto rule;
                CHECK(!rule.detect("	for (auto i = 64; i < len; i += 64) {", "dd"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                LoopRuleSuggestauto rule;
                rule.resetData();
            }
        }
    }
}