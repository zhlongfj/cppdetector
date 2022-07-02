#include "../../doctest.h"
#include "detectors/memleak/memleakrule_newwithoutdelete.h"

static constexpr auto code1 = R"delimiter(
void MemLeakRuleNewWithOutDeleteDemo()
{
    char* p = new char;
    p = nullptr;
}
)delimiter";

static constexpr auto code2 = R"delimiter(
void MemLeakRuleNewWithOutDeleteDemo()
{
    char* p = new char;
    delete p;
    p = nullptr;
}
)delimiter";

SCENARIO("MemLeakRuleNewWithOutDelete") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                MemLeakRuleNewWithOutDelete rule;
                rule.detect(code1, "dd.h");
                rule.resetData();
                CHECK(rule.getRuleErrors().size() == 1);
            }
        }
        WHEN("Mismatch condition") {
            THEN("Mismatching rule") {
                MemLeakRuleNewWithOutDelete rule;
                rule.detect(code2, "dd.h");
                rule.resetData();
                CHECK(rule.getRuleErrors().empty());
            }
        }
    }
}