#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"
#include "detectorcommon/fordefinition.h"

class DETECTOR_EXPORT LoopRuleWrongStepDirection final : public Rule {
public:
    LoopRuleWrongStepDirection();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::unique_ptr<ForDefinition> m_forDefinition;
};

REGISTER_CLASS(LoopRuleWrongStepDirection)
