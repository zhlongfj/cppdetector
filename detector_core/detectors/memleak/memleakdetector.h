#pragma once
#include "detectors/detector.h"
#include "../../common/reflecter.h"
#include "memleakrule_newwithoutdelete.h"
#include "memleakrule_realloc.h"
#include "memleakrule_mallocfree.h"
#include "memleakrule_filehandle.h"
#include "memleakrule_destructor.h"

class MemLeakDetector final : public Detector {
public:
    MemLeakDetector()
        :Detector("MemLeakDetector")
    {
    }

    vector<string> getRuleNames() override
    {
#ifdef WIN32
        return {
            GETRULENAMES(MemLeakRuleNewWithOutDelete),
            GETRULENAMES(MemLeakRuleRealloc),
            GETRULENAMES(MemLeakRuleMallocFree),
            GETRULENAMES(MemLeakRuleFileHandle),
            GETRULENAMES(MemLeakRuleDestructor)
        };
#else
        return {
            "MemLeakRuleNewWithOutDelete",
            "MemLeakRuleRealloc",
            "MemLeakRuleMallocFree",
            "MemLeakRuleFileHandle",
            "MemLeakRuleDestructor"
        };
#endif
    }
};

REGISTER_CLASS(MemLeakDetector)