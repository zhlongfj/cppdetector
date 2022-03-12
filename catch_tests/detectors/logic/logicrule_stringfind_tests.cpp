#include "../../catch.hpp"
#include "detectors/logic/logicrule_stringfind.h"

static constexpr auto code = R"delimiter(
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

SCENARIO("LogicRuleStringFind", "") {
    GIVEN("") {
        WHEN("") {
            THEN("no explicit") {
                LogicRuleStringFind rule;
				CHECK(rule.detect(code, "dd"));
				CHECK(rule.getRuleErrors().size() == 2);
            }
        }
    }
}