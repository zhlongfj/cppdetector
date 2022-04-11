//
// Created by Hualong Zhang on 2021/4/26.
//
#include "../../catch.hpp"
#include "detectors/memleak/memleakrule_filehandle.h"

static constexpr auto code1 = R"delimiter(
void MemLeakRuleFileHandleDemo1()
{
    FILE* pFile = fopen("c:\\test.txt", "w+");
}
)delimiter";

static constexpr auto code2 = R"delimiter(
void MemLeakRuleFileHandleDemo2()
{
    FILE* pFile = fopen("c:\\test.txt", "w+");
    fclose(pFile);
}
)delimiter";

SCENARIO("MemLeakRuleFileHandle", "") {
    GIVEN("") {
        WHEN("Match condition") {
            THEN("Matching rule1") {
                MemLeakRuleFileHandle rule;
                rule.detect(code1, "dd.h");
                rule.resetData();
                CHECK(rule.getRuleErrors().size() == 1);
            }
            THEN("Matching rule2") {
                MemLeakRuleFileHandle rule;
                rule.detect(code2, "dd.h");
                rule.resetData();
                CHECK(rule.getRuleErrors().empty());
            }
        }
    }
}