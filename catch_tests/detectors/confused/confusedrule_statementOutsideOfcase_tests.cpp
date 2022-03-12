#include "../../catch.hpp"
#include<regex>
#include "detectors/confused/confusedrule_statementOutsideOfcase.h"

static constexpr auto code1 = R"delimiter(
void ConfusedRuleStatementOutsideOfCaseDemo(int b)
{
    int c = 0;
    switch (b)
    {
        c = 3;// case之前不应该有代码
    case 2:
        //
        c = 2;
        break;
    default:
        break;
    }
}
)delimiter";

SCENARIO("ConfusedRuleStatementOutsideOfCase", "") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                ConfusedRuleStatementOutsideOfCase rule;
                CHECK(rule.detect(code1, "dd.h"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                ConfusedRuleStatementOutsideOfCase rule;
                rule.resetData();
            }
        }
    }
}