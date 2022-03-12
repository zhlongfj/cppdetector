#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"

class IteratorRuleOutOfBound final : public Rule {
public:
    IteratorRuleOutOfBound();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::string m_sizeVariable;
};

REGISTER_CLASS(IteratorRuleOutOfBound)
