#include "../../catch.hpp"
#include "detectors/confused/confusedrule_constructor.h"

SCENARIO("ConfusedRuleConstructor", "") {
    GIVEN("") {
        WHEN("") {
            THEN("no explicit") {
                ConfusedRuleConstructor rule;
                CHECK(rule.detect("class DDD", "dd") == false);
                CHECK(rule.detect("DDD(int d)", "dd") == true);
                CHECK(rule.getRuleErrors().size() == 1);
            }
            THEN("find explicit") {
                ConfusedRuleConstructor rule;
                CHECK(rule.detect("class DDD", "dd") == false);
                CHECK(rule.detect("explicit DDD(int d)", "dd") == false);
                CHECK(rule.getRuleErrors().empty());
            }
            THEN("not single parameter") {
                ConfusedRuleConstructor rule;
                CHECK(rule.detect("class DDD", "dd") == false);
                CHECK(rule.detect("DDD(int d, int s)", "dd") == false);
                CHECK(rule.detect("DDD( )", "dd") == false);
                CHECK(rule.getRuleErrors().empty());
            }
            THEN("call constructor") {
                ConfusedRuleConstructor rule;
                CHECK(rule.detect("class StringHelp", "dd") == false);
                CHECK(rule.detect("return StringHelper(reference).isDigit() && stoi(reference) >= module;", "dd") == false);
                CHECK(rule.getRuleErrors().empty());
            }
            THEN("call constructor with space") {
                ConfusedRuleConstructor rule;
                CHECK(rule.detect("class StringHelp", "dd") == false);
                CHECK(rule.detect("return StringHelper( reference ).isDigit() && stoi(reference) >= module;", "dd") == false);
                CHECK(rule.getRuleErrors().empty());
            }
            THEN("inherit & consructor with class qualifier") {
                ConfusedRuleConstructor rule;
                CHECK(rule.detect("class DetectorContext", "dd") == false);
                CHECK(rule.detect("class SingleThreadDetectorContext : public DetectorContext", "dd") == false);
                CHECK(rule.detect("SingleThreadDetectorContext(const string& resultDir);", "dd") == true);
                CHECK(rule.detect("SingleThreadDetectorContext::SingleThreadDetectorContext(const string& resultDir)", "dd") == false);
                CHECK(rule.getRuleErrors().size() == 1);
            }
            THEN("paramter with template") {
                ConfusedRuleConstructor rule;
                CHECK(rule.detect("class MapHelp", "dd") == false);
                CHECK(rule.detect("MapHelp(const map<string, T>& elements) : m_elements(elements) {}", "dd") == true);
                CHECK(rule.getRuleErrors().size() == 1);
            }
            THEN("copy constructor") {
                ConfusedRuleConstructor rule;
                CHECK(!rule.detect("class A {", "dd"));
                CHECK(!rule.detect("A(const A & s)", "dd"));
            }
        }
        WHEN("just called") {
            THEN("called") {
                ConfusedRuleConstructor rule;
                rule.resetData();
            }
        }
    }
}