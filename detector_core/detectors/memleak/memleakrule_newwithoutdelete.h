#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"

class MemLeakRuleNewWithOutDelete final : public Rule {
public:
    MemLeakRuleNewWithOutDelete();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::multimap<std::string, ErrorFile> m_objectCreateByNew;
};

REGISTER_CLASS(MemLeakRuleNewWithOutDelete)
