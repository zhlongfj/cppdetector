#pragma once
#include "detectors/detector.h"
#include "../../common/reflecter.h"
#include "classrule_pairofconstructorandassignment.h"

class ClassDetector final: public Detector {
public:
    ClassDetector()
        :Detector("ClassDetector")
    {
    }

    vector<string> getRuleNames() override
    {
#ifdef WIN32
        return {
            GETRULENAMES(VariableRulePairOfConstructorAndAssignment)
        };
#else
        return {
            "VariableRulePairOfConstructorAndAssignment"
        };
#endif
    }
};

REGISTER_CLASS(ClassDetector)