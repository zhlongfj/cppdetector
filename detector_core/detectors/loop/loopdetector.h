#pragma once
#include "detectors/detector.h"
#include "../../common/reflecter.h"
#include "looprule_wrongvariable.h"
#include "looprule_outofbounds.h"
#include "looprule_suggestauto.h"
#include "looprule_wrongstepdirection.h"

class LoopDetector final : public Detector {
public:
    LoopDetector()
        :Detector("LoopDetector")
    {
    }

    vector<string> getRuleNames() override
    {
#ifdef WIN32
        return {
            GETRULENAMES(LoopRuleWrongVariable),
            GETRULENAMES(LoopRuleOutOfBounds),
            GETRULENAMES(LoopRuleSuggestauto),
            GETRULENAMES(LoopRuleWrongStepDirection)
        };
#else
        return {
            "LoopRuleWrongVariable",
            "LoopRuleOutOfBounds",
            "LoopRuleSuggestauto",
            "LoopRuleWrongStepDirection"
        };
#endif
    }
};

REGISTER_CLASS(LoopDetector)