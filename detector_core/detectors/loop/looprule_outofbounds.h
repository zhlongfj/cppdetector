#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"

class DETECTOR_EXPORT LoopRuleOutOfBounds final : public Rule {
public:
    LoopRuleOutOfBounds();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::string m_loopVariable;
};

REGISTER_CLASS(LoopRuleOutOfBounds)
