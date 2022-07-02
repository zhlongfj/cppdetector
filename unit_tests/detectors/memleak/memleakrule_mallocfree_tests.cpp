#include "../../doctest.h"
#include "detectors/memleak/memleakrule_destructor.h"
#include "../../../detector_core/detectors/memleak/memleakrule_mallocfree.h"

static constexpr auto code1 = R"delimiter(
void MemLeakRuleReallocDemo()
{
    char* buf = (char*)malloc(10);
    char* p = buf[1];
    buf = (char*)realloc(buf, 100);
    *p = 'a';
    free(buf);
}
)delimiter";

SCENARIO("MemLeakRuleMallocFree") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                MemLeakRuleMallocFree rule;
                CHECK(rule.detect(code1, "dd.h"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                MemLeakRuleMallocFree rule;
                rule.resetData();
            }
        }
    }
}