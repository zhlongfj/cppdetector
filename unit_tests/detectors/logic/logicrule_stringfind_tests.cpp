#include "../../doctest.h"
#include "detectors/logic/logicrule_stringfind.h"

static constexpr auto code1 = R"delimiter(
void Demo(std::string &str, std::string &search)
{
	// string的find返回的结果应该跟string::npos来判定
	if( string::npos <= str.find(search))
	{
		
	}
	if( 0 == str.find(search))
	{
	}
}
)delimiter";

static constexpr auto code2 = R"delimiter(
void LogicRuleStringFindDemo(std::string& str, std::string& search)
{
    if (0 <= str.find(search))
    {
    }
}
)delimiter";

SCENARIO("LogicRuleStringFind") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                LogicRuleStringFind rule;
				CHECK(rule.detect(code1, "dd"));
            }
            THEN("Matching rule") {
                LogicRuleStringFind rule;
                CHECK(rule.detect(code2, "dd"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                LogicRuleStringFind rule;
                rule.resetData();
            }
        }
    }
}