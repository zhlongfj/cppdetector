#pragma once
#include "detectors/detector.h"
#include "../../common/reflecter.h"
#include "operationrule_zerodivision.h"
#include "operationrule_arithmeticwithbool.h"
#include "operationrule_module.h"
#include "operationrule_float.h"
#include "operationrule_unsignedlessthanzero.h"
#include "operationrule_bitwiseshifttonegative.h"
#include "operationrule_bitwisewithbool.h"

class OperationDetector final : public Detector {
public:
    OperationDetector()
        :Detector("OperationDetector")
    {
    }

    vector<string> getRuleNames() override
    {
#ifdef WIN32
        return {
            GETRULENAMES(OperationRuleZeroDivision),
            GETRULENAMES(OperationRuleArithmeticWithBool),
            GETRULENAMES(OperationRuleModule),
            GETRULENAMES(OperationRuleFloat),
            GETRULENAMES(OperationRuleUnsignedLessThanZero),
            GETRULENAMES(OperationRuleBitwiseShiftToNegative),
            GETRULENAMES(OperationRuleBitwiseWithBool)
        };
#else
        return {
            "OperationRuleZeroDivision",
            "OperationRuleArithmeticWithBool",
            "OperationRuleModule",
            "OperationRuleFloat",
            "OperationRuleUnsignedLessThanZero",
            "OperationRuleBitwiseShiftToNegative",
            "OperationRuleBitwiseWithBool"
        };
#endif // WIN32
    }
};

REGISTER_CLASS(OperationDetector)