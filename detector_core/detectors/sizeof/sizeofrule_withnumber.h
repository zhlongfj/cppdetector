#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include <string>

class SizeOfRuleWithNumber final : public Rule {
public:
    SizeOfRuleWithNumber();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::string m_arrayName;
};

REGISTER_CLASS(SizeOfRuleWithNumber)
