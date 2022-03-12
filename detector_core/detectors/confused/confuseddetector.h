#pragma once
#include "detectors/detector.h"
#include "../../common/reflecter.h"
#include "confusedrule_semicolon.h"
#include "confusedrule_break.h"
#include "confusedrule_priority.h"
#include "confusedrule_prioritywithassignmentandcompare.h"
#include "confusedrule_casewithoutbreak.h"
#include "confusedrule_statementOutsideOfcase.h"
#include "confusedrule_conditionrepeat.h"
#include "confusedrule_returnbool.h"
#include "confusedrule_assignmentinassertorif.h"
#include "confusedrule_switchwihtoutdefault.h"
#include "confusedrule_constructor.h"
#include "confusedrule_diffvariablewithinitandcondition.h"
#include "confusedrule_nothandlefuncreturn.h"

class ConfusedDetector final : public Detector {
public:
    ConfusedDetector()
        :Detector("ConfusedDetector")
    {
    }

    vector<string> getRuleNames() override
    {
#ifdef WIN32
        return {
            GETRULENAMES(ConfusedRuleSemicolon),
            GETRULENAMES(ConfusedRuleBreak),
            GETRULENAMES(ConfusedRulePriority),
            GETRULENAMES(ConfusedRulePriorityWithAssignmentAndCompare),
            GETRULENAMES(ConfusedRuleCaseWithoutBreak),
            GETRULENAMES(ConfusedRuleStatementOutsideOfCase),
            GETRULENAMES(ConfusedRuleConditionRepeat),
            GETRULENAMES(ConfusedRuleAssignmentInAssertOrIf),
            GETRULENAMES(ConfusedRuleReturnBool),
            GETRULENAMES(ConfusedRuleSwitchWithoutDefault),
            GETRULENAMES(ConfusedRuleConstructor),
            GETRULENAMES(ConfusedRuleDiffVariableWithInitAndCondition),
            GETRULENAMES(ConfusedRuleNotHandleFuncReturn)
        };
#else
        return {
            "ConfusedRuleSemicolon",
            "ConfusedRuleBreak",
            "ConfusedRulePriority",
            "ConfusedRulePriorityWithAssignmentAndCompare",
            "ConfusedRuleCaseWithoutBreak",
            "ConfusedRuleStatementOutsideOfCase",
            "ConfusedRuleConditionRepeat",
            "ConfusedRuleAssignmentInAssertOrIf",
            "ConfusedRuleReturnBool",
            "ConfusedRuleSwitchWithoutDefault",
            "ConfusedRuleConstructor",
            "ConfusedRuleDiffVariableWithInitAndCondition",
            "ConfusedRuleNotHandleFuncReturn"
        };
#endif
    }
};

REGISTER_CLASS(ConfusedDetector)