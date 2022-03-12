#include "../../catch.hpp"
#include<regex>
#include "detectors/accesscontrol/accesscontrolrule_membervariable.h"

SCENARIO("AccessControlRuleMemberVariable", "") {
    GIVEN("") {
        WHEN("Class does not declare access rights") {
            THEN("Matching rule: The default access right is private") {
                AccessControlRuleMemberVariable rule;
                auto content =
                    "class AA {\n"
                    "    int i;\n";
                CHECK(!rule.detect(content, "ss.h"));
            }
        }
        WHEN("Struct does not declare access rights") {
            THEN("Mismatching rule: The default access right is public") {
                AccessControlRuleMemberVariable rule;
                auto content =
                    "struct AA {\n"
                    "    int i;\n";
                CHECK(!rule.detect(content, "ss.h"));
            }
        }
        WHEN("Class declares public access right") {
            THEN("Matching rule") {
                AccessControlRuleMemberVariable rule;
                auto content =
                    "class AA {\n"
                    "public:\n"
                    "    int i;\n";
                CHECK(rule.detect(content, "ss.h"));
            }
        }
        WHEN("Class declares protected access right") {
            THEN("Mismatching rule") {
                AccessControlRuleMemberVariable rule;
                auto content =
                    "class AA {\n"
                    "protected:\n"
                    "    int i;\n";
                CHECK(!rule.detect(content, "ss.h"));
            }
        }
        WHEN("Class declares private access right") {
            THEN("Mismatching rule") {
                AccessControlRuleMemberVariable rule;
                auto content =
                    "class AA {\n"
                    "private:\n"
                    "    int i;\n";
                CHECK(!rule.detect(content, "ss.h"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                AccessControlRuleMemberVariable rule;
                rule.resetData();
            }
        }
    }
}
