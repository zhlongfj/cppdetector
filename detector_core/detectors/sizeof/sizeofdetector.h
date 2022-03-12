#pragma once
#include "detectors/detector.h"
#include "../../common/reflecter.h"
#include "sizeofrule_funcparameter.h"
#include "sizeofrule_repetition.h"
#include "sizeofrule_withnumber.h"
#include "sizeofrule_pointer.h"

class SizeofDetector final : public Detector {
public:
    SizeofDetector()
        :Detector("SizeofDetector")
    {
    }

    vector<string> getRuleNames() override
    {
#ifdef WIN32
        return {
            GETRULENAMES(SizeOfRuleFuncParameter),
            GETRULENAMES(SizeOfRuleRepetition),
            GETRULENAMES(SizeOfRuleWithNumber),
            GETRULENAMES(SizeOfRulePointer)
        };
#else
        return {
            "SizeOfRuleFuncParameter",
            "SizeOfRuleRepetition",
            "SizeOfRuleWithNumber",
            "SizeOfRulePointer"
        };
#endif
    }
};

REGISTER_CLASS(SizeofDetector)