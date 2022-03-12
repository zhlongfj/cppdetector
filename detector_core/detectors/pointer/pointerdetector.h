#pragma once
#include "detectors/detector.h"
#include "pointerrule_nullptr.h"
#include "pointerrule_usedoutsideofcheck.h"
#include "pointerrule_usedinsideofnullcheck.h"
#include "pointerrule_notcheck.h"
#include "pointerrule_useduninitialized.h"
#include "pointerrule_usednull.h"
#include "pointerrule_useddanglingpointer.h"
#include "pointerrule_ifnulldefect.h"
#include "../../common/reflecter.h"
#include "pointerrule_localvariable.h"
#include "pointerrule_returnnull.h"
#include "pointerrule_checkafternew.h"

class PointerDetector final : public Detector {
public:
    PointerDetector()
        :Detector("PointerDetector")
    {
    }

    vector<string> getRuleNames() override
    {
#ifdef WIN32
        return {
            GETRULENAMES(PointerRuleCheckAfterNew),
            GETRULENAMES(PointerRuleNullptr),
            GETRULENAMES(PointerRuleUsedOutsideOfCheck),
            GETRULENAMES(PointerRuleUsedInsideOfNULLCheck),
            GETRULENAMES(PointerRuleNotCheck),
            GETRULENAMES(PointerRuleUsedUninitialized),
            GETRULENAMES(PointerRuleUsedNull),
            GETRULENAMES(PointerRuleUsedDanglingPointer),
            GETRULENAMES(PointerRuleIfNullDefect),
            GETRULENAMES(PointerRuleLocalVariable),
            GETRULENAMES(PointerRuleReturnNull)
        };
#else
        return {
            "PointerRuleCheckAfterNew",
            "PointerRuleNullptr",
            "PointerRuleUsedOutsideOfCheck",
            "PointerRuleUsedInsideOfNULLCheck",
            "PointerRuleNotCheck",
            "PointerRuleUsedUninitialized",
            "PointerRuleUsedNull",
            "PointerRuleUsedDanglingPointer",
            "PointerRuleIfNullDefect",
            "PointerRuleLocalVariable",
            "PointerRuleReturnNull"
        };
#endif
    }
};

REGISTER_CLASS(PointerDetector)