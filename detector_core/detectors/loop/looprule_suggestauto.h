#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"

class LoopRuleSuggestauto final : public Rule {
public:
    LoopRuleSuggestauto();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::string m_loopVariable;
};

REGISTER_CLASS(LoopRuleSuggestauto)
