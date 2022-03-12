#include "../../catch.hpp"
#include<regex>
#include "detectors/inline/inlinerule_specialclassmethod.h"

static constexpr auto code1 = R"delimiter(
class AA {
    inline AA(){}
    inline ~AA(){}
    inline virtual DD(){}
    virtual DD1(){}
    inline DD2(){} override
)delimiter";

SCENARIO("InlineRuleTenLines", "") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                InlineRuleSpecialClassMethod rule;
                CHECK(!rule.detect(code1, "ss.h"));
            }
        }
        WHEN("Mismatch condition") {
            THEN("Mismatching rule") {
                InlineRuleSpecialClassMethod rule;
                CHECK(!rule.detect("ffg", "ss.cpp"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                InlineRuleSpecialClassMethod rule;
                rule.resetData();
            }
        }
    }
}
