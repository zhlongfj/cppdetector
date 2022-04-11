#include "../../catch.hpp"
#include "detectors/confused/confusedrule_break.h"

static constexpr auto code1 = R"delimiter(
int ConfusedRuleBreakDemo(int iMax)
{
    int iCount = 0;
	while (iCount < iMax)
    {
		break;
        iCount++;
    }
    return iCount;
}
)delimiter";

static constexpr auto code2 = R"delimiter(
void func111()
{
    for (int i = 0; i < 10; i++)
    {
        switch (vecParagraph[i].horizontalAlignment)
        {
        case HAlignment::HCENTER:
        {
            qstrAlign = " align=\"CENTER\">";
        }
        break;
        case HAlignment::HLEFT:
        {
            qstrAlign = " align=\"LEFT\">";
        }
        break;
        case HAlignment::HRIGHT:
        {
            qstrAlign = " align=\"RIGHT\">";
        }
        break;
        }
        break;
    }
)delimiter";

static constexpr auto code3 = R"delimiter(
void func111()
{
    for (int i = 0; i < 10; i++) {
        switch (vecParagraph[i].horizontalAlignment) {
        case HAlignment::HCENTER:
        {
            qstrAlign = " align=\"CENTER\">";
        }
        break;
        case HAlignment::HLEFT:
        {
            qstrAlign = " align=\"LEFT\">";
        }
        break;
        case HAlignment::HRIGHT:
        {
            qstrAlign = " align=\"RIGHT\">";
        }
        break;
        }
        break;
    }
)delimiter";

SCENARIO("ConfusedRuleBreak", "") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                ConfusedRuleBreak rule;
                CHECK(rule.detect(code1, "dd.h"));
                CHECK(rule.detect(code2, "dd.h"));
                CHECK(rule.detect(code3, "dd.h"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                ConfusedRuleBreak rule;
                rule.resetData();
            }
        }
    }
}