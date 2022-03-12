#include "../../catch.hpp"
#include<regex>
#include "detectors/class/classrule_pairofconstructorandassignment.h"

static constexpr auto sss = R"delimiter(
class A
{
public:
    A(const int s)
    {

    }

    A(const A& s)
    {

    }

    A& operator=(const A&& a)
    {

    }
}; 
)delimiter";

SCENARIO("VariableRulePairOfConstructorAndAssignment", "") {
    GIVEN("") {
        WHEN("") {
            THEN("bad smell") {
                VariableRulePairOfConstructorAndAssignment rule;
                rule.detect(sss, "ddd");
                CHECK(rule.getRuleErrors().size() == 2);
            }
        }
    }
}