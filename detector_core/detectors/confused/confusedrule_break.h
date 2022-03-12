#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"

class BraceHelper;
class DETECTOR_EXPORT ConfusedRuleBreak final : public Rule {
public:
    ConfusedRuleBreak();
    ~ConfusedRuleBreak();
    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::unique_ptr<BraceHelper> m_braceHelper;
    std::string m_indexOfLoop;
    std::string::size_type m_indexOfSwitch = string::npos;
    int m_countOfBraceInSwitch = 0;
};

REGISTER_CLASS(ConfusedRuleBreak)
