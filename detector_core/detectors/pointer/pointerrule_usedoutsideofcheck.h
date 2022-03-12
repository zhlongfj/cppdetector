#pragma once
#include "../rule.h"
#include "common/reflecter.h"
#include "detector_global.h"
#include <string>
#include <vector>

class DETECTOR_EXPORT PointerRuleUsedOutsideOfCheck final : public Rule {
public:
    PointerRuleUsedOutsideOfCheck();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::string m_objName;
    std::vector<bool> m_inConditions;
    bool m_findBrace = false;
};

REGISTER_CLASS(PointerRuleUsedOutsideOfCheck)
