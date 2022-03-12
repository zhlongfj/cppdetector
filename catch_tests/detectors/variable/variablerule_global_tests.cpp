#include "../../catch.hpp"
#include<regex>
#include "detectors/variable/variablerule_global.h"

SCENARIO("VariableRuleGlobal", "") {
    GIVEN("normal class declaration") {
        WHEN("without 'virtual' in the destructor declaration and without 'final' in the class declaration") {
            THEN("bad smell") {
                VariableRuleGlobal rule;
                //CHECK(rule.detect("DetectorContext ss;", "") == true);
                CHECK(rule.detect("const  std::vector<std::string> MoveTypeNames{ \"CLOCK_WISE\" , \"ANTI_CLOCK_WISE\",\"MARQUEE_LEFT\" };", "") == true);
                CHECK(rule.detect("std::string ViplexCoreAsync::m_sdkRootDir;", "") == false);
                CHECK(rule.detect("DDD &&d;", "") == true);
                CHECK(rule.detect("int &&d;", "") == false);
                CHECK(rule.detect("DDD && d;", "") == true);
                CHECK(rule.detect("int && d;", "") == false);
                CHECK(rule.detect("DDD&& d;", "") == true);
                CHECK(rule.detect("int&& d;", "") == false);
                CHECK(rule.detect("DetectorContext ss = 0;", "") == true);
                CHECK(rule.detect("vector<string> ss = {\"dfs\", \"dfs\"};", "") == true);
                CHECK(rule.detect("static vector<string> ss = {\"dfs\", \"dfs\"};", "") == true);
                CHECK(rule.detect("const static vector<string> ss = {\"dfs\", \"dfs\"};", "") == true);
                CHECK(rule.detect("int i = 0;", "") == false);
                CHECK(rule.detect("    int i = 0;", "") == false);
                CHECK(rule.detect("int i[4] = {0,1,2,3};", "") == false);
                CHECK(rule.detect("const string&g_jCurrentTime = \"currentTime\";", "") == false);
                CHECK(rule.detect("const string& g_jWificollectorinfo = \"wificollectorinfo\";", "") == false);
                CHECK(rule.detect("const string &g_jWificollectorinfo = \"wificollectorinfo\";", "") == false);
                CHECK(rule.detect("const string & g_jWificollectorinfo = \"wificollectorinfo\";", "") == false);
                CHECK(rule.detect("std::shared_ptr<PlayFont> m_playFont;", "") == false);
            }
            THEN("bad smell") {
                VariableRuleGlobal rule;
                CHECK(rule.detect("class AA {", "") == false);
                CHECK(rule.detect("    DetectorContext ss; ", "") == false);
                CHECK(rule.detect("    DetectorContext ss = 0;", "") == false);
                CHECK(rule.detect("    vector<string> ss = {\"dfs\", \"dfs\"};", "") == false);
                CHECK(rule.detect("    static vector<string> ss = {\"dfs\", \"dfs\"};", "") == true);
                CHECK(rule.detect("    const static vector<string> ss = {\"dfs\", \"dfs\"};", "") == true);
                CHECK(rule.detect("    int i = 0;", "") == false);
                CHECK(rule.detect("    int i[4] = {0,1,2,3};", "") == false);
                CHECK(rule.detect("};", "") == false);
                CHECK(rule.detect("    DetectorContext ss;", "") == true);
                CHECK(rule.detect("DetectorContext ss = 0;", "") == true);
                CHECK(rule.detect("vector<string> ss = {\"dfs\", \"dfs\"};", "") == true);
            }
            THEN("bad smell") {
                VariableRuleGlobal rule;
                CHECK(rule.detect("void func() {", "") == false);
                CHECK(rule.detect("    DetectorContext ss; ", "") == false);
                CHECK(rule.detect("    DetectorContext ss = 0;", "") == false);
                CHECK(rule.detect("    vector<string> ss = {\"dfs\", \"dfs\"};", "") == false);
                CHECK(rule.detect("    static vector<string> ss = {\"dfs\", \"dfs\"};", "") == false);
                CHECK(rule.detect("    const static vector<string> ss = {\"dfs\", \"dfs\"};", "") == false);
                CHECK(rule.detect("    int i = 0;", "") == false);
                CHECK(rule.detect("    int i[4] = {0,1,2,3};", "") == false);
                CHECK(rule.detect("}", "") == false);
                CHECK(rule.detect("    DetectorContext ss;", "") == true);
                CHECK(rule.detect("DetectorContext ss = 0;", "") == true);
                CHECK(rule.detect("vector<string> ss = {\"dfs\", \"dfs\"};", "") == true);
            }
            THEN("bad smell") {
                VariableRuleGlobal rule;
                CHECK(rule.detect("using namespace std;", "") == false);
                CHECK(rule.detect("using RuleContents = vector<shared_ptr<RuleContent>>;", "") == false);
                CHECK(rule.detect("extern \"C\"", "") == false);
                CHECK(rule.detect("extern string g_dd", "") == false);
                CHECK(rule.detect("class DDD;", "") == false);
            }
        }
    }
}