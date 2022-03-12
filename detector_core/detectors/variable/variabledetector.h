#pragma once
#include "detectors/detector.h"
#include "../../common/reflecter.h"
#include "variablerule_global.h"

class VariableDetector final: public Detector {
public:
    VariableDetector()
        :Detector("VariableDetector")
    {
    }

    vector<string> getRuleNames() override
    {
#ifdef WIN32
        return {
            GETRULENAMES(VariableRuleGlobal)
        };
#else
        return {
            "VariableRuleGlobal"
        };
#endif
    }
};

REGISTER_CLASS(VariableDetector)