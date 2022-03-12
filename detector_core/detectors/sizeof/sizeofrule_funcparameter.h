#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"

class SizeOfRuleFuncParameter final : public Rule {
public:
    SizeOfRuleFuncParameter();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::string m_arrayName;
};

REGISTER_CLASS(SizeOfRuleFuncParameter)
