#include "../../catch.hpp"
#include "detectors/iterator/iteratorrule_invaliddereference.h"

static constexpr auto code1 = R"delimiter(
void IteratorRuleInvalidDereferenceDemo()
{
    std::vector<int>& ivec;
    std::vector<int>::iterator iter = ivec.begin();
    if (iter == ivec.end()){
        iter->value_type;
        cout << *iter;
    }
}
)delimiter";

static constexpr auto code2 = R"delimiter(
void IteratorRuleInvalidDereferenceDemo2()
{
    std::vector<int>& ivec;
    std::vector<int>::iterator iter = ivec.begin();
    if (ivec.end() == ivec.find(3))
    {
        ivec.find(3)->value_type;
        cout << *(ivec.find(3));
    }
}
)delimiter";

SCENARIO("IteratorRuleInvalidDereference", "") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                IteratorRuleInvalidDereference rule;
                CHECK(rule.detect(code1, "ss.h"));
                CHECK(rule.detect(code2, "ss.h"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                IteratorRuleInvalidDereference rule;
                rule.resetData();
            }
        }
    }
}
