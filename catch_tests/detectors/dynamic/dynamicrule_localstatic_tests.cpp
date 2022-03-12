#include "../../catch.hpp"
#include<regex>
#include "detectors/dynamic/dynamicrule_localstatic.h"

static constexpr auto code1 = R"delimiter(
class OUTPUT Test1() {
    static Test1& getInstance() {
        static Test1 test;
        return test;
    }
}

class OUTPUT Test2() {
    static Test2& getInstance() {
        static Test2 test;
        return test;
    }
}
)delimiter";

SCENARIO("DynamicRuleLocalStatic", "") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                DynamicRuleLocalStatic rule;
                CHECK(rule.detect(code1, "dd.h"));
                CHECK(rule.getRuleErrors().size() == 2);
            }
        }
        WHEN("just called") {
            THEN("called") {
                DynamicRuleLocalStatic rule;
                rule.resetData();
            }
        }
    }
}