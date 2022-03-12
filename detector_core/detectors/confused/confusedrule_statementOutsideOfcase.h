#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"

class DETECTOR_EXPORT ConfusedRuleStatementOutsideOfCase final : public Rule {
public:
    ConfusedRuleStatementOutsideOfCase();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    bool m_inSwitch = false;
    bool m_inCase = false;
};

REGISTER_CLASS(ConfusedRuleStatementOutsideOfCase)
