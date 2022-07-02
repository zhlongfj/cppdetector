#include "../../doctest.h"
#include "detectors/inline/inlinerule_recursion.h"

SCENARIO("InlineRuleRecursion") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                InlineRuleRecursion rule;
                string ss = 
                    "inline void func(){\n"
                    "    func();\n"
                    "}\n";
                CHECK(rule.detect(ss, "ss.h"));
            }
        }
        WHEN("Mismatch condition") {
            THEN("Mismatching rule") {
                InlineRuleRecursion rule;
                string ss =
                    "inline void func(){\n"
                    "    func1();\n"
                    "}\n";
                CHECK(!rule.detect(ss, "ss.h"));
            }
        }
    }
}
