#pragma once
#include "detectors/detector.h"
#include "../../common/reflecter.h"
#include "logicrule_basevalue.h"
#include "logicrule_incorrectoperation.h"
#include "logicrule_assignself.h"
#include "logicrule_stringfind.h"
#include "logicrule_expressionrepetition.h"
#include "detector_global.h"

class DETECTOR_EXPORT LogicDetector final : public Detector {
public:
    LogicDetector()
        :Detector("LogicDetector")
    {
    }

    vector<string> getRuleNames() override
    {
#ifdef WIN32
        return {
            GETRULENAMES(LogicRuleBaseValue),
            GETRULENAMES(LogicRuleIncorrectOperation),
            GETRULENAMES(LogicRuleAssignSelf),
            GETRULENAMES(LogicRuleStringFind),
            GETRULENAMES(LogicRuleExpressionRepetition)
        };
#else
        return {
            "LogicRuleBaseValue",
            "LogicRuleIncorrectOperation",
            "LogicRuleAssignSelf",
            "LogicRuleStringFind",
            "LogicRuleExpressionRepetition"
        };
#endif
    }
};

REGISTER_CLASS(LogicDetector)