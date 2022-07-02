#include "../../doctest.h"
#include "detectors/confused/confusedrule_returnbool.h"

static constexpr auto code1 = R"delimiter(
bool ConfusedRuleReturnBoolRetFunc()
{
    if (rand() > 10)
    {
        return 10;
    }
    return 1;
}
)delimiter";

SCENARIO("ConfusedRuleReturnBool") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                ConfusedRuleReturnBool rule;
                CHECK(rule.detect(code1, "dd.h"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                ConfusedRuleReturnBool rule;
                rule.resetData();
            }
        }
    }
}