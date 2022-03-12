#pragma once
#include "detectors/detector.h"
#include "../../common/reflecter.h"
#include "arrayrule_indexoutofbounds.h"
#include "arrayrule_indexusedbeforecheck.h"
#include "arrayrule_indexcheckdefectively.h"
#include "arrayrule_bufferoverflow.h"
#include "arrayrule_indexoutofboundsfromfunc.h"
#include "arrayrule_indexoutofboundsinloop.h"
#include "arrayrule_memsetzerobyte.h"
//#include "Visual Leak Detector/include/vld.h"
//#pragma comment(lib, "vld.lib")

class ArrayDetector final : public Detector {
public:
    ArrayDetector()
        :Detector("ArrayDetector")
    {
    }

    vector<string> getRuleNames() override
    {
#ifdef WIN32
        return {
            GETRULENAMES(ArrayRuleIndexOutOfBounds),
            GETRULENAMES(ArrayRuleIndexUsedBeforeCheck),
            GETRULENAMES(ArrayRuleIndexCheckDefectively),
            GETRULENAMES(ArrayRuleBufferOverflow),
            GETRULENAMES(ArrayRuleIndexOutOfBoundsFromFunc),
            GETRULENAMES(ArrayRuleIndexOutOfBoundsInLoop),
            GETRULENAMES(ArrayRuleMemsetZeroByte)
        };
#else
        return {
            "ArrayRuleIndexOutOfBounds",
            "ArrayRuleIndexUsedBeforeCheck",
            "ArrayRuleIndexCheckDefectively",
            "ArrayRuleBufferOverflow",
            "ArrayRuleIndexOutOfBoundsFromFunc",
            "ArrayRuleIndexOutOfBoundsInLoop",
            "ArrayRuleMemsetZeroByte"
        };
#endif
    }
};

REGISTER_CLASS(ArrayDetector)