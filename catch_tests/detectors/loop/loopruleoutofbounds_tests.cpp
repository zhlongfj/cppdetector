#include "../../catch.hpp"
#include<regex>
#include "detectors/loop/looprule_outofbounds.h"

SCENARIO("LoopRuleOutOfBounds", "") {
    GIVEN("") {
        WHEN("") {
            THEN("no explicit") {
                LoopRuleOutOfBounds rule;
                CHECK(!rule.detect("	for (int i = 64; i < len; i += 64) {", "dd"));
                CHECK(!rule.detect("		if (pubKey[i] != '\n') {", "dd"));
            }
        }
    }
}