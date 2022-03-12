#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"

class DETECTOR_EXPORT ConfusedRuleConstructor final : public Rule {
public:
    ConfusedRuleConstructor();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::string m_className;
};

REGISTER_CLASS(ConfusedRuleConstructor)
