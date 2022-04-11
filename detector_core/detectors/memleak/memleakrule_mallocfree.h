#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"

class DETECTOR_EXPORT MemLeakRuleMallocFree final : public Rule {
public:
    MemLeakRuleMallocFree();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;
};

REGISTER_CLASS(MemLeakRuleMallocFree)
