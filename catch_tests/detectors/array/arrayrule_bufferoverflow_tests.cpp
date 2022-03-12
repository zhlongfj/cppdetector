#include "../../catch.hpp"
#include "detectors/array/arrayrule_bufferoverflow.h"
#include "../../../detector_core/detectors/array/arrayrulehelper.h"

static constexpr auto strcpyCode = R"delimiter(
char sz[2];
strcpy(sz, "123");
)delimiter";

static constexpr auto strncpyCode = R"delimiter(
char sz[MAX1];
strncpy(sz, "123", 3);
)delimiter";

static constexpr auto strcatCode = R"delimiter(
char szStrTime[5];
char source[10] = { "abcde" };
strcat(szStrTime, source);
)delimiter";

static constexpr auto snprintfCode = R"delimiter(
char szStrTime[5];
char source[10] = { "abcde" };
snprintf(szStrTime, 5, "%s", source);
)delimiter";

SCENARIO("ArrayRuleBufferOverflow", "") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                ArrayRuleBufferOverflow rule;
                CHECK(rule.detect(strcpyCode, "dd.h"));
                CHECK(rule.detect(strncpyCode, "dd.h"));
                CHECK(rule.detect(snprintfCode, "dd.h"));
            }
        }
        WHEN("") {
            THEN("") {
                std::unique_ptr<ArrayRuleHelper> helper = make_unique<ArrayRuleHelper>();
                helper->setData("char source[10] = { \"abcde\" };");
                ArrayRuleBufferOverflow rule(move(helper));
                CHECK(rule.detect(strcatCode, "dd.h"));
            }
        }
        WHEN("Abnormal scenario") {
            THEN("MisMatching rule") {
                ArrayRuleBufferOverflow rule;
                CHECK(!rule.detect("strstr(s, b)", "dd.h"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                ArrayRuleBufferOverflow rule;
                rule.resetData();
            }
        }
    }
}
