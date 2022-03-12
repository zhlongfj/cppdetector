#pragma once
#include "detectors/detector.h"
#include "singletonrule_threadsafety.h"
#include "../../common/reflecter.h"

class SingletonDetector final : public Detector {
public:
    SingletonDetector()
        :Detector("SingletonDetector")
    {
    }

    vector<string> getRuleNames() override
    {
#ifdef WIN32
        return {
            GETRULENAMES(SingletonRuleThreadSafety)
        };
#else
        return {
            "SingletonRuleThreadSafety"
        };
#endif
    }
};

REGISTER_CLASS(SingletonDetector)