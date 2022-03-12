#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include <regex>
#include "detector_global.h"

class FunctionDefinition;
class DETECTOR_EXPORT ConfusedRuleNotHandleFuncReturn final : public Rule {
public:
    ConfusedRuleNotHandleFuncReturn();
    ~ConfusedRuleNotHandleFuncReturn();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::unique_ptr<FunctionDefinition> m_functionDefinition;
    std::set<std::string> m_funcsWithReturn;
};

REGISTER_CLASS(ConfusedRuleNotHandleFuncReturn)
