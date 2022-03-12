#include "../../catch.hpp"
#include<regex>
#include "detectors/confused/confusedrule_conditionrepeat.h"
#include "detectorcommon/detectorhelp.h"

static constexpr auto code1 = R"delimiter(
void func()
{
    if (!programRegular.constraints.empty() && programRegular.programID != -1)
    {
    }
    if (!programRegular.constraints.empty() && programRegular.programID != -1)
    {
    }
}
)delimiter";

static constexpr auto code2 = R"delimiter(
int Demo(int a, int b)
{
	// if和elseif的条件是一样的
	if(a == b)
	{
		return 1;
	}
	else if(a == b)
	{
		return 2;
	}
	
	return 0;
}
)delimiter";

static constexpr auto code3 = R"delimiter(
int Demo(int a, int b)
{
    if (PasswordSuccessful != result)
        result = verifyNew(enteredNewPSD);
    if (PasswordSuccessful != result)
}
)delimiter";

SCENARIO("ConfusedRuleConditionRepeat", "") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule in two if statements") {
                ConfusedRuleConditionRepeat rule;
                CHECK(rule.detect(code1, "dd"));
            }
            THEN("Matching rule in if else statements") {
                ConfusedRuleConditionRepeat rule;
                CHECK(rule.detect(code2, "dd"));
            }
        }
        WHEN("Abnormal scenario") {
            THEN("MisMatching rule") {
                ConfusedRuleConditionRepeat rule;
                CHECK(!rule.detect(R"delimiter("dfdfd" \)delimiter", "dd.h"));
                CHECK(!rule.detect(code3, "dd"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                ConfusedRuleConditionRepeat rule;
                rule.resetData();
            }
        }
    }
}