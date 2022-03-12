#include "../../catch.hpp"
#include<regex>
#include "detectors/logic/logicrule_expressionrepetition.h"

SCENARIO("LogicExpressionRepetition", "") {
    GIVEN("") {
        WHEN("") {
            THEN("no explicit") {
                LogicRuleExpressionRepetition rule;
                CHECK(!rule.detect("assert(parent != nullptr && pData != nullptr);", "dd"));
                CHECK(!rule.detect(" if (rc_ != SQLITE_ROW && rc_ != SQLITE_DONE)", "dd"));
                CHECK(!rule.detect(" if (rc_ != SQLITE_ROW && rc_ != SQLITE_DONE)", "dd"));

                CHECK(rule.detect(" if (rc_ != SQLITE_ROW && rc_ != SQLITE_ROW)", "dd"));
                CHECK(rule.detect(" if (rc_ == SQLITE_ROW && rc_ == SQLITE_ROW)", "dd"));
                CHECK(rule.detect("if (a >= 10 && a >= 20)", "dd"));
            }
        }
    }
}