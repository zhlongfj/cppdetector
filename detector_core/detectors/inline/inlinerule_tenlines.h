#pragma once
#include "../rule.h"
#include "common/reflecter.h"
#include "detector_global.h"

class BraceHelper;
class DETECTOR_EXPORT InlineRuleTenLines final : public Rule {
public:
    InlineRuleTenLines();

    ~InlineRuleTenLines();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;
    void resetData() override;

private:
    std::unique_ptr<BraceHelper> braceHelper;
    bool m_isInline = false;
    int m_lineOfFunction = 0;
};

REGISTER_CLASS(InlineRuleTenLines)
