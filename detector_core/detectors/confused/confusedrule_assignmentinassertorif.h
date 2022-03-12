#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include <regex>
#include "detector_global.h"

class DETECTOR_EXPORT ConfusedRuleAssignmentInAssertOrIf final : public Rule {
public:
    ConfusedRuleAssignmentInAssertOrIf();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::string makeCondition(const std::string& code, const std::string& prefix);
    bool isAssignment(const string& code);
    std::smatch checkOperator(const std::string& code, const std::string& arithmetic);
};

REGISTER_CLASS(ConfusedRuleAssignmentInAssertOrIf)
