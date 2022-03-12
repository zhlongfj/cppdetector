#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"

class MemLeakRuleFileHandle final : public Rule {
public:
    MemLeakRuleFileHandle();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::multimap<std::string, ErrorFile> m_resources;
};

REGISTER_CLASS(MemLeakRuleFileHandle)
