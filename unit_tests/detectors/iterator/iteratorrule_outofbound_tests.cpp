#include "../../doctest.h"
#include "detectors/iterator/iteratorrule_outofbound.h"

static constexpr auto code1 = R"delimiter(
void IteratorRuleOutOfBoundDemo()
{
    std::vector<int> foo;
    for (unsigned int ii = 0; ii <= foo.size(); ++ii)
    {
        foo[ii] = 0;
    }
}
)delimiter";

static constexpr auto code2 = R"delimiter(
void IteratorRuleOutOfBoundDemo2()
{
    std::vector<int> foo;
    auto ss = foo.size();
    for (unsigned int ii = 0; ii <= ss; ++ii)
    {
        foo[ii] = 0;
    }
}
)delimiter";

SCENARIO("IteratorRuleOutOfBound") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule1") {
                IteratorRuleOutOfBound rule;
                CHECK(rule.detect(code1, "ss.h"));
            }
            THEN("Matching rule2") {
                IteratorRuleOutOfBound rule;
                CHECK(rule.detect(code2, "ss.h"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                IteratorRuleOutOfBound rule;
                rule.resetData();
            }
        }
    }
}
