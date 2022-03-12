#pragma once
#include "../rule.h"
#include "common/reflecter.h"
#include "detector_global.h"

class DETECTOR_EXPORT DynamicRuleLocalStatic final : public Rule {
public:
    DynamicRuleLocalStatic();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::string m_className;
};

REGISTER_CLASS(DynamicRuleLocalStatic)
