#pragma once
#include "detectors/detector.h"
#include "../../common/reflecter.h"
#include "uninitrule_var.h"
#include "uninitrule_pointer.h"

class UninitDetector final : public Detector {
public:
    UninitDetector()
        :Detector("UninitDetector")
    {
    }

    vector<string> getRuleNames() override
    {
#ifdef WIN32
        return {
            GETRULENAMES(UninitRuleVar),
            GETRULENAMES(UninitRulePointer)
        };
#else
        return {
            "UninitRuleVar",
            "UninitRulePointer"
        };
#endif
    }
};

REGISTER_CLASS(UninitDetector)