#pragma once
#include "detectorcommon/bracehelper.h"
#include "../rule.h"
#include "detectorcommon/detectorhelp.h"
#include "common/reflecter.h"

class ClassDefinition;

class DETECTOR_EXPORT InlineRuleSpecialClassMethod final : public Rule {
public:
    InlineRuleSpecialClassMethod();

    ~InlineRuleSpecialClassMethod();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::unique_ptr<ClassDefinition> classDefinition;
};

REGISTER_CLASS(InlineRuleSpecialClassMethod)
