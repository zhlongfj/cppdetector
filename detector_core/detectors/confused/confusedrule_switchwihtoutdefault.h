#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"

class DETECTOR_EXPORT ConfusedRuleSwitchWithoutDefault final: public Rule {
public:
    ConfusedRuleSwitchWithoutDefault();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::vector<ErrorFile> m_errorFiles;
    bool m_inSwitch = false;
};

REGISTER_CLASS(ConfusedRuleSwitchWithoutDefault)
