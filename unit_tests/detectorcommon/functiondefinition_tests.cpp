#include "../doctest.h"
#include "../../detector_core/detectorcommon/functiondefinition.h"


SCENARIO("FunctionDefinition") {
    GIVEN("") {
        WHEN("") {
            THEN("function call") {
                FunctionDefinition definition;
                CHECK(!definition.inFunctionDefinition("DD::func(3);"));
                //CHECK(definition.inFunctionDefinition("ViplexCore::getInstance().getSearchTerminal()->serchTerminal([&, starttime, timeout](const uint16_t code, const char * data)") == false);
            }
            THEN("Single-Row Function") {
                FunctionDefinition definition;
                CHECK(!definition.inFunctionDefinition("void DD::func(int a) {}"));
                CHECK(!definition.inFunctionDefinition("    void DD::func(int a) {}"));
                CHECK(!definition.inFunctionDefinition("bool findOpenBrace() { return m_findOpenBrace; }"));
            }
            THEN("Inside the function and outside the function") {
                FunctionDefinition definition;
                CHECK(definition.inFunctionDefinition("    void DD::func(int a) {"));
                CHECK(definition.inFunctionDefinition("        int i = 0;"));
                CHECK(definition.inFunctionDefinition("    }"));
                CHECK(!definition.inFunctionDefinition("int i = 0;"));
            }
            THEN("Various forms of function definition") {
                FunctionDefinition definition;
                CHECK(definition.inFunctionDefinition("    shared_ptr<DetectorError> getDetectorError() {"));
                CHECK(definition.inFunctionDefinition("static void* createObject(const std::string& className)"));
                CHECK(definition.inFunctionDefinition("inline static std::map<std::string, Constructor>& constructors()"));
                CHECK(definition.inFunctionDefinition("static void* createObject(const std::string& className)"));
                CHECK(definition.inFunctionDefinition("static void registerClass(std::string className, Constructor constructor)"));
                CHECK(definition.inFunctionDefinition("void Demo(std::vector<int>& ivec)"));
            }
            THEN("A function with multiple lines of arguments") {
                FunctionDefinition definition;
                CHECK(definition.inFunctionDefinition("int httptTools::progressCallback(void *p,"));
                CHECK(definition.inFunctionDefinition("	curl_off_t dltotal,"));
                CHECK(definition.inFunctionDefinition("	curl_off_t ulnow)"));
                CHECK(definition.inFunctionDefinition("{}"));
                CHECK(!definition.inFunctionDefinition("int i = 0;"));
                definition.resetData();
                CHECK(definition.inFunctionDefinition("int* DemoFunc()"));
            }
            THEN("Abnormal scenario") {
                FunctionDefinition definition;
                CHECK(!definition.inFunctionDefinition("else if(a == b)"));
            }
            THEN("Complete function definition") {
                FunctionDefinition definition;
                CHECK(definition.inFunctionDefinition("bool isFor(const std::string & content)"));
                CHECK(definition.inFunctionDefinition("{"));
                CHECK(definition.inFunctionDefinition("    auto ret = DetectorHelper::checkFor1(content);"));
                CHECK(definition.inFunctionDefinition("    if (ret.empty())"));
                CHECK(definition.inFunctionDefinition("    {"));
                CHECK(definition.inFunctionDefinition("        return false;"));
                CHECK(definition.inFunctionDefinition("    }"));
                CHECK(definition.inFunctionDefinition("}"));
            }
        }
    }
}