#include "../catch.hpp"
#include "common/stringhelper.h"

SCENARIO("StringHelper", "") {
    GIVEN("") {
        WHEN("") {
            THEN("realloc") {
                StringHelper helper("else if (buf = (char*)realloc(buf, 100))");
                CHECK(helper.findCode("realloc"));
            }
            THEN("") {
                StringHelper helper("++i");
                CHECK(helper.getVariableFromSelfOperation("++") == "i");
            }
            THEN("") {
                StringHelper helper("i--");
                CHECK(helper.getVariableFromSelfOperation("--") == "i");
            }
        }
    }
}