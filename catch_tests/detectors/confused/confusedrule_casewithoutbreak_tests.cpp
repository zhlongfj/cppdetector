#include "../../catch.hpp"
#include<regex>
#include "detectors/confused/confusedrule_casewithoutbreak.h"

static constexpr auto code1 = R"delimiter(
void dd()
{
    int param = 4;
    string qstrAlign;
    switch (param)
    {
    case 1:
    {
        qstrAlign = " align=\"CENTER\">";
        int param1 = 3;
        switch (param1)
        {
        case 3:
            qstrAlign = " align=\"RIGHT\">";
        default:
            qstrAlign = " align=\"RIGHT\">";
        }
    }
    case 2:
        qstrAlign = " align=\"LEFT\">";
        break;
    case 3:
        qstrAlign = " align=\"RIGHT\">";
    default:
        qstrAlign = " align=\"RIGHT\">";
    }
}
)delimiter";

SCENARIO("ConfusedRuleCaseWithoutBreak", "") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                ConfusedRuleCaseWithoutBreak rule;
                rule.detect(code1, "dd.h");
                rule.resetData();
                CHECK(rule.getRuleErrors().size() == 4);
            }
        }
    }
}