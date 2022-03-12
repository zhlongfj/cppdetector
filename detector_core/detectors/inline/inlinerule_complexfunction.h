#pragma once
#include "../rule.h"
#include "common/reflecter.h"
#include "detector_global.h"


class DETECTOR_EXPORT InlineRuleComplexFunction final : public Rule {
public:
    InlineRuleComplexFunction();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    bool m_isInline = false;
    int m_lineOfFunction = 0;
    std::string m_spacesBeforeFunction;
};

REGISTER_CLASS(InlineRuleComplexFunction)
