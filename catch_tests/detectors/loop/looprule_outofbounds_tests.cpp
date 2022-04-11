#include "../../catch.hpp"
#include "detectors/loop/looprule_outofbounds.h"

static constexpr auto code1 = R"delimiter(
void LoopRuleOutOfBoundsDemo(std::string& str, char ch)
{
    for (std::string::const_iterator iter = str.begin(); iter != str.end(); ++iter)
    {
        if (*(iter + 1) == ch)
        {
        }
    }
}
)delimiter";

SCENARIO("LoopRuleOutOfBounds", "") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                LoopRuleOutOfBounds rule;
                CHECK(rule.detect(code1, "dd"));
            }
        }
        WHEN("Mismatch condition") {
            THEN("Mismatching rule") {
                LoopRuleOutOfBounds rule;
                CHECK(!rule.detect("	for (int i = 64; i < len; i += 64) {", "dd"));
                CHECK(!rule.detect("		if (pubKey[i] != '\n') {", "dd"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                LoopRuleOutOfBounds rule;
                rule.resetData();
            }
        }
    }
}