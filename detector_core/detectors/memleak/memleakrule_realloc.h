#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"

class DETECTOR_EXPORT MemLeakRuleRealloc final : public Rule {
public:
    MemLeakRuleRealloc();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;
};

REGISTER_CLASS(MemLeakRuleRealloc)
