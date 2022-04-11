#include "../../catch.hpp"
#include "detectors/dynamic/dynamicrule_inline.h"

static constexpr auto code1 = R"delimiter(
class OUTPUT Test
{
public:
    void f() {}
};

class OUTPUT Test2 : public Test
{
public:
    void ff() 
	{
		FF::dd();
	}
};
)delimiter";

SCENARIO("DynamicRuleInline", "") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                DynamicRuleInline rule;
                CHECK(!rule.detect(code1, "dd.h"));
                rule.resetData();
                CHECK(rule.getRuleErrors().size() == 1);
            }
        }
    }
}