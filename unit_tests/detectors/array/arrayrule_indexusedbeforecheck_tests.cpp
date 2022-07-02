#include "../../doctest.h"
#include "detectors/array/arrayrulehelper.h"
#include "detectors/array/arrayrule_indexusedbeforecheck.h"

static constexpr auto code1 = R"delimiter(
#define INDEX 200
void indexusedbeforedcheckDemo(int index)
{
    char buf[10] = { 0 };
    if (buf[index] > 0 && index <= INDEX)
        return;
}
)delimiter";

static constexpr auto code2 = R"delimiter(
#define INDEX 200
void indexusedbeforedcheckDemo(int index)
{
    char buf[10] = { 0 };
    if (buf[index] > 0
        && index < INDEX)
        return;
}
)delimiter";

static constexpr auto code3 = R"delimiter(
#define INDEX 200
void indexusedbeforedcheckDemo(int index)
{
    char buf[10] = { 0 };
    if (buf[index] > 0 &&
        index < INDEX)
        return;
}
)delimiter";

static constexpr auto code4 = R"delimiter(
#define INDEX 200
void indexusedbeforedcheckDemo(int index)
{
    char buf[10] = { 0 };
    if (buf[index] > 0)
        return;
}
)delimiter";

SCENARIO("ArrayRuleIndexUsedBeforeCheck") {
    GIVEN("") {
        WHEN("Match condition with define outside1") {
            THEN("Matching rule") {
                std::unique_ptr<ArrayRuleHelper> helper = make_unique<ArrayRuleHelper>();
                helper->setData(code1);
                ArrayRuleIndexUsedBeforeCheck rule(move(helper));
                CHECK(rule.detect(code1, "dd.h"));
            }
        }
        WHEN("Match condition with define outside2") {
            THEN("Matching rule") {
                std::unique_ptr<ArrayRuleHelper> helper = make_unique<ArrayRuleHelper>();
                helper->setData(code2);
                ArrayRuleIndexUsedBeforeCheck rule(move(helper));
                CHECK(rule.detect(code2, "dd.h"));
            }
        }
        WHEN("Match condition with define outside3") {
            THEN("Matching rule") {
                std::unique_ptr<ArrayRuleHelper> helper = make_unique<ArrayRuleHelper>();
                helper->setData(code3);
                ArrayRuleIndexUsedBeforeCheck rule(move(helper));
                CHECK(rule.detect(code3, "dd.h"));
            }
        }
        WHEN("Match condition with define outside4") {
            THEN("Missatching rule") {
                std::unique_ptr<ArrayRuleHelper> helper = make_unique<ArrayRuleHelper>();
                helper->setData(code4);
                ArrayRuleIndexUsedBeforeCheck rule(move(helper));
                CHECK(!rule.detect(code4, "dd.h"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                ArrayRuleIndexUsedBeforeCheck rule;
                rule.resetData();
            }
        }
    }
}
