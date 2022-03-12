#pragma once
#include "detectors/detector.h"
#include "../../common/reflecter.h"
#include "iteratorrule_outofbound.h"
#include "iteratorrule_invaliddereference.h"

class IteratorDetector final : public Detector {
public:
    IteratorDetector()
        :Detector("IteratorDetector")
    {
    }

    vector<string> getRuleNames() override
    {
#ifdef WIN32
        return {
            GETRULENAMES(IteratorRuleOutOfBound),
            GETRULENAMES(IteratorRuleInvalidDereference)
        };
#else
        return {
            "IteratorRuleOutOfBound",
            "IteratorRuleInvalidDereference"
        };
#endif
    }
};

REGISTER_CLASS(IteratorDetector)