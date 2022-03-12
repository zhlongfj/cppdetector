#pragma once
#include "../rule.h"
#include "common/reflecter.h"
#include "detector_global.h"
#include <string>

class DETECTOR_EXPORT PointerRuleLocalVariable final : public Rule {
public:
    PointerRuleLocalVariable();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    bool m_bInFunction = false;
    std::string m_localVariableType;
    std::string m_localVariable;
};

REGISTER_CLASS(PointerRuleLocalVariable)
