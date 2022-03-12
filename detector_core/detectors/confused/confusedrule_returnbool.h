#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"

class DETECTOR_EXPORT ConfusedRuleReturnBool final : public Rule {
public:
    ConfusedRuleReturnBool();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    bool m_returnTypeIsBool = false;
};

REGISTER_CLASS(ConfusedRuleReturnBool)
