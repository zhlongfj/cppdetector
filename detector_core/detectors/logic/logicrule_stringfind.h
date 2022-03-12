#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"

class DETECTOR_EXPORT LogicRuleStringFind final : public Rule {
public:
    LogicRuleStringFind();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    bool checkValid(const std::string& code);
};

REGISTER_CLASS(LogicRuleStringFind)
