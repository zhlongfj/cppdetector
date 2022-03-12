#include "../../catch.hpp"
#include "detectors/array/arrayrule_memsetzerobyte.h"

static constexpr auto code1 = R"delimiter(
void ArrayRuleMemsetDemo()
{
    char* p = new char[100];
    memset(p, 100, 0);
    delete[] p;
}
)delimiter";

static constexpr auto code2 = R"delimiter(
void ArrayRuleMemsetDemo()
{
    char* p = new char[100];
    auto ss = "memset(p, 100, 0);";
    delete[] p;
}
)delimiter";

SCENARIO("ArrayRuleMemsetZeroByte", "") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                ArrayRuleMemsetZeroByte rule;
                CHECK(rule.detect(code1, "dd.h"));
            }
        }
        WHEN("Not match condition") {
            THEN("Mismatching rule") {
                ArrayRuleMemsetZeroByte rule;
                CHECK(!rule.detect(code2, "dd.h"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                ArrayRuleMemsetZeroByte rule;
                rule.resetData();
            }
        }
    }
}
