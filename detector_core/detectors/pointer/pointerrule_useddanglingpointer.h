#pragma once
#include "../rule.h"
#include "common/reflecter.h"

class PointerRuleUsedDanglingPointer final : public Rule {
public:
    PointerRuleUsedDanglingPointer();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::string getObjectName(const std::string& code);

    std::set<std::string> m_objNames;
};

REGISTER_CLASS(PointerRuleUsedDanglingPointer)
