#include "../catch.hpp"
#include "detectorcommon/detectorhelp.h"
#include "detectorcommon/fordefinition.h"

SCENARIO("ForDefinition", "") {
    GIVEN("checkConstructedObject") {
        WHEN("") {
            THEN("Iteration variables are declared in loops") {
                string code = R"delimiter(for (unsigned int ii = 0; ii <= foo.size(); ++ii))delimiter";
                ForDefinition definition;
                CHECK(definition.isFor(code));
                CHECK(definition.type() == "unsigned int");
            }
            THEN("Iteration variables are declared outside the loop") {
                string code = R"delimiter(for (ii = 0; ii <= foo.size(); ++ii))delimiter";
                ForDefinition definition;
                CHECK(definition.isFor(code));
                CHECK(definition.type() == "");
            }
            THEN("Reverse loop") {
                string code = R"delimiter(for (ii = foo.size() - 1; ii >= 0; ii--))delimiter";
                ForDefinition definition;
                CHECK(definition.isFor(code));
                CHECK(definition.type() == "");
            }
            THEN("") {
                string code = R"delimiter(while (d))delimiter";
                ForDefinition definition;
                CHECK(!definition.isFor(code));
            }
        }
    }
}