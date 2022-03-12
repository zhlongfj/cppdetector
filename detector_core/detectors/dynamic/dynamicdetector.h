#pragma once
#include "detectors/detector.h"
#include "dynamicrule_localstatic.h"
#include "dynamicrule_inline.h"

class DynamicDetector final : public Detector {
public:
    DynamicDetector()
        :Detector("DynamicDetector")
    {
    }

    vector<string> getRuleNames() override
    {
#ifdef WIN32
        return {
            GETRULENAMES(DynamicRuleLocalStatic),
            GETRULENAMES(DynamicRuleInline)
        };
#else
        return {
            "DynamicRuleLocalStatic",
            "DynamicRuleInline"
        };
#endif
    }
};

REGISTER_CLASS(DynamicDetector)