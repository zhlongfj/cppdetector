#include "../catch.hpp"
#include "detectorcommon/detectorhelp.h"

SCENARIO("DetectorHelper", "") {
    GIVEN("checkConstructedObject") {
        WHEN("new") {
            THEN("parameter name") {
                string code = "int *p = new int";
                auto ret = DetectorHelper::checkConstructedObject(code);
                CHECK(ret[1].str() == "p");
            }
        }
        WHEN("make_shared") {
            THEN("parameter name") {
                string code = "std::shared_ptr<std::string> var = std::make_shared<std::string>()";
                auto ret = DetectorHelper::checkConstructedObject(code);
                CHECK(ret[1].str() == "var");
            }
        }
        WHEN("make_unique") {
            THEN("parameter name") {
                string code = "std::unique_ptr<string> var1 = std::make_unique<string>()";
                auto ret = DetectorHelper::checkConstructedObject(code);
                CHECK(ret[1].str() == "var1");
            }
        }
        WHEN("reset") {
            THEN("parameter name") {
                string code = "var2.reset(new int);";
                auto ret = DetectorHelper::checkConstructedObject(code);
                CHECK(ret[1].str() == "var2");
            }
        }
    }
    GIVEN("isFunctionDefinition")
    {
        WHEN("return value is point")
        {
            string code = "int* DemoFunc()";
            auto ret = DetectorHelper::getReturnTypeOfFunctionDefinition(code);
            CHECK(ret.empty());
        }
    }
}