#pragma once
#include "detectors/detector.h"
#include "../../common/reflecter.h"
#include "accesscontrolrule_membervariable.h"

class AccessControlDetector final : public Detector {
public:
    AccessControlDetector()
        :Detector("AccessControlDetector")
    {
    }

    vector<string> getRuleNames() override
    {
#ifdef WIN32
        return {
            GETRULENAMES(AccessControlRuleMemberVariable)
        };
#else
        return {
            "AccessControlRuleMemberVariable"
        };
#endif
    }
};

REGISTER_CLASS(AccessControlDetector)