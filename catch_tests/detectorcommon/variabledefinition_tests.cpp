#include "../catch.hpp"
#include "../../detector_core/detectorcommon/functiondefinition.h"
#include "detectorcommon/variabledefinition.h"

SCENARIO("VariableDefinition", "") {
    GIVEN("") {
        WHEN("") {
            THEN("no explicit") {
                VariableDefinition definition;
                CHECK(!definition.isVariableDefinition("d == 0 ? dd : dsf"));
                CHECK(!definition.isVariableDefinition("ArrayRuleIndexOutOfBoundsFromFunc final :  Rule"));
                CHECK(!definition.isVariableDefinition(R"delimiter(std::cout << "ss" << width << " * " << height << endl;)delimiter"));
                CHECK(!definition.isVariableDefinition(R"delimiter(dd >> dd)delimiter"));
                CHECK(definition.isVariableDefinition("DD a "));
                CHECK(!definition.isVariableDefinition("{"));
                CHECK(!definition.isVariableDefinition("DD a(int i)"));
                CHECK(!definition.isVariableDefinition("DD a(int&i)"));
                CHECK(!definition.isVariableDefinition("DD a(int*i)"));
                CHECK(definition.isVariableDefinition("DD a(dd)"));
                CHECK(definition.isVariableDefinition("DD a(3,34,\"ddfs\")"));
                CHECK(definition.isVariableDefinition("DD a(3,"));
                CHECK(!definition.isVariableDefinition("DD a()"));
                CHECK(!definition.isVariableDefinition("void a(int i)"));
                CHECK(!definition.isVariableDefinition("void func()"));
                CHECK(definition.isVariableDefinition("DD a{3,"));
                CHECK(definition.isVariableDefinition("DD a"));
                CHECK(definition.isVariableDefinition("DD a = {3,"));
                CHECK(definition.isVariableDefinition("DD a = DD(3,"));
                CHECK(definition.isVariableDefinition("DD a = DD(dd)"));
                CHECK(definition.isVariableDefinition("const  std::vector<std::string> MoveTypeNames{ \"CLOCK_WISE\" , \"ANTI_CLOCK_WISE\",\"MARQUEE_LEFT\" };") == true);
                CHECK(definition.isVariableDefinition("std::string ViplexCoreAsync::m_sdkRootDir;"));
                CHECK(definition.isVariableDefinition("DDD &&d;"));
                CHECK(definition.isVariableDefinition("int &&d;"));
                CHECK(definition.isVariableDefinition("DDD && d;"));
                CHECK(definition.isVariableDefinition("int && d;"));
                CHECK(definition.isVariableDefinition("DDD&& d;"));
                CHECK(definition.isVariableDefinition("int&& d;"));
                CHECK(definition.isVariableDefinition("int * d;"));
                CHECK(!definition.isInitialized());
                CHECK(definition.isVariableDefinition("int * d = NULL;"));
                CHECK(definition.isPoint());
                CHECK(definition.name() == "d");
                CHECK(definition.isInitialized());
                CHECK(definition.isVariableDefinition("int ** d;"));
                CHECK(definition.isPointToPoint());
                CHECK(definition.isVariableDefinition("int ** d = nullptr;"));
                CHECK(definition.isVariableDefinition("DetectorContext ss = 0;"));
                CHECK(definition.isVariableDefinition("vector<string> ss = {\"dfs\", \"dfs\"};"));
                CHECK(definition.isVariableDefinition("static vector<string> ss = {\"dfs\", \"dfs\"};"));
                CHECK(definition.isVariableDefinition("const static vector<string> ss = {\"dfs\", \"dfs\"};"));
                CHECK(definition.isVariableDefinition("int i = 0;"));
                CHECK(definition.isVariableDefinition("    int i = 0;"));
                CHECK(definition.isVariableDefinition("int i[4] = {0,1,2,3};"));
                CHECK(definition.isVariableDefinition("const string&g_jCurrentTime = \"currentTime\";"));
                CHECK(definition.isVariableDefinition("const string& g_jWificollectorinfo = \"wificollectorinfo\";"));
                CHECK(definition.isVariableDefinition("const string &g_jWificollectorinfo = \"wificollectorinfo\";"));
                CHECK(definition.isVariableDefinition("const string & g_jWificollectorinfo = \"wificollectorinfo\";"));
                CHECK(definition.isVariableDefinition("std::shared_ptr<PlayFont> m_playFont;"));
                bool isNotPoint = definition.isVariableDefinition("std::vector<VObject*> m_children;") && !definition.isPoint();
                CHECK(isNotPoint);
            }
        }
    }
}