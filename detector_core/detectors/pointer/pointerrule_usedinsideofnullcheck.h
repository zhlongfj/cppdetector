#pragma once
#include "../rule.h"
#include "common/reflecter.h"
#include "detector_global.h"

class IfDefinition;
class DETECTOR_EXPORT PointerRuleUsedInsideOfNULLCheck final : public Rule {
public:
    PointerRuleUsedInsideOfNULLCheck();
    ~PointerRuleUsedInsideOfNULLCheck();
    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::string getObjNameFromIf(const string& code);

    std::string m_objName;
    std::vector<bool> m_inConditions;
    std::unique_ptr<IfDefinition> m_ifDefinition;
};

REGISTER_CLASS(PointerRuleUsedInsideOfNULLCheck)
