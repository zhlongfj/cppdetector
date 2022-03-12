#include "../../catch.hpp"
#include<regex>
#include "detectors/inline/inlinerule_complexfunction.h"

SCENARIO("InlineRuleComplexFunction", "") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                InlineRuleComplexFunction rule;

                CHECK(!rule.detect("inline void func(){", "ss.h"));
                CHECK(rule.detect("for (", "ss.h"));

                CHECK(!rule.detect("inline void func(){", "ss.h"));
                CHECK(rule.detect("switch (", "ss.h"));

                CHECK(!rule.detect("inline void func(){", "ss.h"));
                CHECK(rule.detect("while (", "ss.h"));
            }
        }
        WHEN("Mismatch condition") {
            THEN("Mismatching rule") {
                InlineRuleComplexFunction rule;
                CHECK(!rule.detect("void func(){", "ss.h"));
                CHECK(!rule.detect("for (", "ss.h"));

                CHECK(!rule.detect("inline void func(){", "ss.h"));
                CHECK(!rule.detect("\"for (\"", "ss.h"));
            }
        }
    }
}
