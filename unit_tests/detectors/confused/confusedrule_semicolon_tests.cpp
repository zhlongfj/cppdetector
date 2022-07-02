#include "../../doctest.h"
#include "detectors/confused/confusedrule_semicolon.h"

static constexpr auto code1 = R"delimiter(
void ConfusedRuleSemicolonDemo(int iMax)
{
    if (iMax > 0 && iMax != 3);
    {

    }
}
)delimiter";

static constexpr auto code2 = R"delimiter(
void ConfusedRuleSemicolonDemo(int iMax)
{
    do 
    {
        int i = 0;
    } while (true);
}
)delimiter";

SCENARIO("ConfusedRuleSemicolon") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                ConfusedRuleSemicolon rule;
                CHECK(rule.detect(code1, "dd.h"));
            }
        }
        WHEN("Mismatch condition") {
            THEN("Mismatching rule") {
                ConfusedRuleSemicolon rule;
                CHECK(!rule.detect(code2, "dd.h"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                ConfusedRuleSemicolon rule;
                rule.resetData();
            }
        }
    }
}