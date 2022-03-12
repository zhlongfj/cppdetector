#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"

class MemLeakRuleMallocFree final : public Rule {
public:
    MemLeakRuleMallocFree();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;
};

REGISTER_CLASS(MemLeakRuleMallocFree)
