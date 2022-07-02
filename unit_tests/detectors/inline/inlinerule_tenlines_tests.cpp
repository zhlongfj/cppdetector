#include "../../doctest.h"
#include "detectors/inline/inlinerule_tenlines.h"

static constexpr auto sss = R"delimiter(
inline void func(){
    int i = 0;
    int i = 0;
    int i = 0;
    int i = 0;
    int i = 0;
    int i = 0;
    int i = 0;
    int i = 0;
    int i = 0;
    int i = 0;
    int i = 0;
}
)delimiter";
SCENARIO("InlineRuleSpecialClassMethod") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                InlineRuleTenLines rule;
                CHECK(!rule.detect("void func(){int i = 0;}", "ss.h"));
                CHECK(!rule.detect("inline void func(){int i = 0;}", "ss.h"));
                CHECK(!rule.detect("void func() {\n    int i = 0;}", "ss.h"));
                CHECK(rule.detect(sss, "ss.h"));
            }
        }
        WHEN("Mismatch condition") {
            THEN("Mismatching rule") {
                InlineRuleTenLines rule;
                CHECK(!rule.detect("void func(){int i = 0;}", "ss.cpp"));
            }
        }
    }
}
