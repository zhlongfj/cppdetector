#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"

class DETECTOR_EXPORT ConfusedRuleSemicolon final : public Rule {
public:
    ConfusedRuleSemicolon();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
};

REGISTER_CLASS(ConfusedRuleSemicolon)
