#pragma once
#include "../rule.h"
#include "common/reflecter.h"
#include "detector_global.h"

class BraceHelper;
class DETECTOR_EXPORT InlineRuleRecursion final : public Rule {
public:
    InlineRuleRecursion();

    ~InlineRuleRecursion();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    unique_ptr<BraceHelper> braceHelper;
    bool m_isInline = false;
    int m_lineOfFunction = 0;
    string m_nameOfFunctionDefinition;
};

REGISTER_CLASS(InlineRuleRecursion)
