#include "../catch.hpp"
#include "../../detector_core/detectorcommon/classdefinition.h"

SCENARIO("ClassDefinition", "") {
    GIVEN("") {
        WHEN("") {
            THEN("class definition") {
                ClassDefinition definition;
                CHECK(definition.inClassDefinition("class A {") == false);
                CHECK(definition.inClassDefinition("    int i = 0;") == true);
                CHECK(definition.inClassDefinition("};") == false);
            }
            THEN("nested class ") {
                ClassDefinition definition;
                CHECK(definition.inClassDefinition("class A {") == false);
                CHECK(definition.inClassDefinition("    class B {") == true);
                CHECK(definition.inClassDefinition("    };") == true);
                CHECK(definition.inClassDefinition("};") == false);
            }
            THEN("check destructor or virtual") {
                ClassDefinition definition;
                CHECK(definition.inClassDefinition("class A {") == false);
                CHECK(definition.isDestructor("    virtual ~A()").first);
                CHECK(definition.isVirtual("    virtual ~A()"));
                CHECK(definition.isVirtual("    void DD() override"));
                CHECK(definition.inClassDefinition("};") == false);
            }
            THEN("check exceptional situation") {
                ClassDefinition definition;
                CHECK(!definition.isVirtual("    int a = 0;"));
                CHECK(definition.getAccessControl("dd") == AccessControl::PRIVATE);

            }
        }
    }
}