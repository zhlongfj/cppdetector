#include "../../catch.hpp"
#include "detectors/array/arrayrulehelper.h"
#include "detectors/array/arrayrule_indexoutofboundsinloop.h"

static constexpr auto code1 = R"delimiter(
#define INDEX 200
void ArrayRuleIndexOutOfBoundsInLoopDemo()
{
    char buf[INDEX];
    for (unsigned int i = 0; i <= INDEX; ++i)
    {
        buf[i] = 'a';
    }

    for (unsigned int i = 0; i < INDEX; ++i)
    {
        buf[i] = 'a';
    }
}
)delimiter";

SCENARIO("ArrayRuleIndexOutOfBoundsInLoop", "") {
    GIVEN("") {
        WHEN("Match condition with define outside") {
            THEN("Matching rule") {
                std::unique_ptr<ArrayRuleHelper> helper = make_unique<ArrayRuleHelper>();
                helper->setData(code1);
                ArrayRuleIndexOutOfBoundsInLoop rule(move(helper));
                CHECK(rule.detect(code1, "dd.h"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                ArrayRuleIndexOutOfBoundsInLoop rule;
                rule.resetData();
            }
        }
    }
}
