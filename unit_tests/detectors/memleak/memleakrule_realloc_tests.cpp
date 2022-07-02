#include "../../doctest.h"
#include "detectors/memleak/memleakrule_realloc.h"

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

SCENARIO("MemLeakRuleRealloc") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                MemLeakRuleRealloc rule;
                CHECK(rule.detect(code1, "dd.h"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                MemLeakRuleRealloc rule;
                rule.resetData();
            }
        }
    }
}