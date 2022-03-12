#include "../../catch.hpp"
#include "detectors/array/arrayrulehelper.h"
#include "detectors/array/arrayrule_indexoutofbounds.h"

static constexpr auto code1 = R"delimiter(
#define MAX 100
#define INDEX 200
constexpr int MAX1 = 100;
constexpr int INDEX1 = 200;
void indexoutofboundsDemo()
{
    int array_temp[100];
    array_temp[200];

    int array_temp1[MAX];
    array_temp1[INDEX];

    int array_temp2[MAX1];
    array_temp2[INDEX1];
}
)delimiter";

static constexpr auto code2 = R"delimiter(
void indexoutofboundsDemo(int b)
{
    int max = 5;
    int a[10];
    if (b > 0)
    {
        max = 10;
    }

    a[max] = max;
}
)delimiter";

SCENARIO("ArrayRuleIndexOutOfBounds", "") {
    GIVEN("") {
        WHEN("Match condition with define outside") {
            THEN("Matching rule") {
                std::unique_ptr<ArrayRuleHelper> helper = make_unique<ArrayRuleHelper>();
                helper->setData(code1);
                ArrayRuleIndexOutOfBounds rule(move(helper));
                CHECK(rule.detect(code1, "dd.h"));
            }
        }
        WHEN("Match condition") {
            THEN("Matching rule") {
                std::unique_ptr<ArrayRuleHelper> helper = make_unique<ArrayRuleHelper>();
                helper->setData(code2);
                ArrayRuleIndexOutOfBounds rule(move(helper));
                CHECK(rule.detect(code2, "dd.h"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                ArrayRuleIndexOutOfBounds rule;
                rule.resetData();
            }
        }
    }
}
