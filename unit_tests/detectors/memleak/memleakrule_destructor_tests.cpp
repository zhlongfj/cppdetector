//
// Created by Hualong Zhang on 2021/4/26.
//
//#define CATCH_CONFIG_MAIN
//#include "../../doctest.h"
#define ANKERL_NANOBENCH_IMPLEMENT
#include "../../nanobench.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../doctest.h"

#include "detectors/memleak/memleakrule_destructor.h"

static constexpr auto codeStruct = R"delimiter(
struct DetectorContext
{
    ~DetectorContext(){}
}
)delimiter";

SCENARIO("MemLeakRuleDestructor") {
    GIVEN("normal class declaration") {
        WHEN("without 'virtual' in the destructor declaration and without 'final' in the class declaration") {
            THEN("bad smell") {
                MemLeakRuleDestructor rule;
                CHECK(rule.detect("class DetectorContext", "") == false);
                CHECK(rule.detect("~DetectorContext()", "") == true);
                CHECK(rule.getRuleErrors().size() == 1);

                CHECK(rule.detect("class DetectorContext: public Context", "") == false);
                CHECK(rule.detect("~DetectorContext()", "") == true);
                CHECK(rule.getRuleErrors().size() == 1);
            }
        }
        WHEN("with 'virtual' in the destructor declaration or with 'final' in the class declaration") {
            THEN("good") {
                MemLeakRuleDestructor rule;
                CHECK(rule.detect("class DetectorContext", "") == false);
                CHECK(rule.detect("virtual ~DetectorContext()", "") == false);

                CHECK(rule.detect("class DetectorContext final", "") == false);
                CHECK(rule.detect("~DetectorContext()", "") == false);

                CHECK(rule.detect("class DetectorContext final : public Context", "") == false);
                CHECK(rule.detect("~DetectorContext()", "") == false);

                CHECK(rule.getRuleErrors().empty());
            }
        }
    }

    GIVEN("export class declaration") {
        WHEN("without 'virtual' in the destructor declaration and without 'final' in the class declaration") {
            THEN("bad smell") {
                MemLeakRuleDestructor rule;
                CHECK(rule.detect("class DDDDD DetectorContext", "") == false);
                CHECK(rule.detect("~DetectorContext()", "") == true);
                CHECK(rule.getRuleErrors().size() == 1);
            }
        }
        WHEN("with 'virtual' in the destructor declaration or with 'final' in the class declaration") {
            THEN("good") {
                MemLeakRuleDestructor rule;
                CHECK(rule.detect("class DDDDD DetectorContext", "") == false);
                CHECK(rule.detect("virtual ~DetectorContext()", "") == false);

                CHECK(rule.detect("class DDDDD DetectorContext final", "") == false);
                CHECK(rule.detect("~DetectorContext()", "") == false);

                CHECK(rule.detect("class DDDDD DetectorContext final : public Context", "") == false);
                CHECK(rule.detect("~DetectorContext()", "") == false);

                CHECK(rule.getRuleErrors().empty());
            }
        }
    }
    GIVEN("struct declaration") {
        WHEN("with 'virtual' in the destructor declaration or with 'final' in the struct declaration") {
            THEN("normal") {
                MemLeakRuleDestructor rule;
                CHECK(!rule.detect(codeStruct, "dd"));
            }
        }
    }
}