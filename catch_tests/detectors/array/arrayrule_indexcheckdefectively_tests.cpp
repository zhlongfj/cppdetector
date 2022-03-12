#include "../../catch.hpp"
#include "detectors/array/arrayrule_indexcheckdefectively.h"
#include "detectors/array/arrayrulehelper.h"

static constexpr auto code1 = R"delimiter(
void indexcheckdefectivelyDemo1(int index)
{
    int buf[10];
    if (index < 0 || index > 10)
    {
        return;
    }
    buf[index] = 3;
}
)delimiter";

static constexpr auto code2 = R"delimiter(
#define MAX 100
void indexcheckdefectivelyDemo2(int index)
{
    int buf[MAX];
    if (index < 0 || index > MAX)
    {
        return;
    }
    buf[index] = 3;
}
)delimiter";

static constexpr auto code3 = R"delimiter(
#define MAX 100
void indexcheckdefectivelyDemo2(int index)
{
    int buf[MAX];
    if (index > MAX)
    {
        return;
    }
    buf[index] = 3;
}
)delimiter";

SCENARIO("ArrayRuleIndexCheckDefectively", "") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                std::unique_ptr<ArrayRuleHelper> helper = make_unique<ArrayRuleHelper>();
                helper->setData(code1);
                ArrayRuleIndexCheckDefectively rule(move(helper));
                CHECK(rule.detect(code1, "dd.h"));
            }
        }
        WHEN("Match condition with define outside") {
            THEN("Matching rule") {
                std::unique_ptr<ArrayRuleHelper> helper = make_unique<ArrayRuleHelper>();
                helper->setData(code2);
                ArrayRuleIndexCheckDefectively rule(move(helper));
                CHECK(rule.detect(code2, "dd.h"));
                rule.resetData();
            }
        }
        WHEN("Match condition with one-way") {
            THEN("Matching rule") {
                std::unique_ptr<ArrayRuleHelper> helper = make_unique<ArrayRuleHelper>();
                helper->setData(code3);
                ArrayRuleIndexCheckDefectively rule(move(helper));
                CHECK(rule.detect(code3, "dd.h"));

            }
        }
        WHEN("just called") {
            THEN("called") {
                ArrayRuleIndexCheckDefectively rule;
                rule.resetData();
            }
        }
    }
}
