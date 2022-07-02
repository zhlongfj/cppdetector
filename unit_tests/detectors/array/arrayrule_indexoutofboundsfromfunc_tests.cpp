#include "../../doctest.h"
#include "detectors/array/arrayrulehelper.h"
#include "detectors/array/arrayrule_indexoutofboundsfromfunc.h"

static constexpr auto code1 = R"delimiter(
constexpr int INDEX1 = 200;
class ArrayRuleIndexOutOfBoundsFromFuncDemo()
{
    char buf[INDEX1];
    int length = getLenFromBuf(INDEX1);
    buf[length] = 'Q';
}
)delimiter";

SCENARIO("ArrayRuleIndexOutOfBoundsFromFunc") {
    GIVEN("") {
        WHEN("Match condition with define outside") {
            THEN("Matching rule") {
                std::unique_ptr<ArrayRuleHelper> helper = make_unique<ArrayRuleHelper>();
                helper->setData(code1);
                ArrayRuleIndexOutOfBoundsFromFunc rule(move(helper));
                CHECK(rule.detect(code1, "dd.h"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                ArrayRuleIndexOutOfBoundsFromFunc rule;
                rule.resetData();
            }
        }
    }
}
