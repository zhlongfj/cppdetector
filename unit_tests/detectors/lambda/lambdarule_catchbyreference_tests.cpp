#include "../../doctest.h"
#include "detectors/lambda/lambdarule_catchbyreference.h"

static constexpr auto code1 = R"delimiter(
void fontManger(startTransferProgram, [&](const int errorCode, const std::string& result) {
}
)delimiter";

static constexpr auto code2 = R"delimiter(
void fontManger(startTransferProgram, [=](const int errorCode, const std::string& result) {
}
)delimiter";

static constexpr auto code3 = R"delimiter(
void fontManger(startTransferProgram, [param1](const int errorCode, const std::string& result) {
}
)delimiter";

SCENARIO("LambdaRuleCatchByReference") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule") {
                LambdaRuleCatchByReference rule;
                CHECK(rule.detect(code1, "ss.h"));
            }
        }
        WHEN("Mismatch condition") {
            THEN("Mismatching rule1") {
                LambdaRuleCatchByReference rule;
                CHECK(!rule.detect(code2, "ss.cpp"));
            }
            THEN("Mismatching rule2") {
                LambdaRuleCatchByReference rule;
                CHECK(!rule.detect(code3, "ss.cpp"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                LambdaRuleCatchByReference rule;
                rule.resetData();
            }
        }
    }
}
