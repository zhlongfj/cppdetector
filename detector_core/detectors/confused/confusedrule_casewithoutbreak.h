#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"

class DETECTOR_EXPORT ConfusedRuleCaseWithoutBreak final : public Rule {
public:
    ConfusedRuleCaseWithoutBreak();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::vector<ErrorFile> m_cases;
    bool m_inSwitch = false;
    bool m_inCase = false;
    std::vector<std::pair<bool, bool>> m_switchState;
};

REGISTER_CLASS(ConfusedRuleCaseWithoutBreak)
