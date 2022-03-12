#pragma once
#include "../rule.h"
#include "common/reflecter.h"

class PointerRuleCheckAfterNew final : public Rule {
public:
    PointerRuleCheckAfterNew();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::string m_pointerNameFromNew;
};

REGISTER_CLASS(PointerRuleCheckAfterNew)
