#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"

class DETECTOR_EXPORT ArrayRuleMemsetZeroByte final : public Rule {
public:
    ArrayRuleMemsetZeroByte();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;
};

REGISTER_CLASS(ArrayRuleMemsetZeroByte)
