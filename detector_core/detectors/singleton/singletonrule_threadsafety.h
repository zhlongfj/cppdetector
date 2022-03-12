#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include <string>

class SingletonRuleThreadSafety final : public Rule {
public:
    SingletonRuleThreadSafety();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

    void clear();

private:
    bool m_findIf = false;
    std::string m_className;
    std::string m_parameterName;
    ErrorFile m_errorFile;
};

REGISTER_CLASS(SingletonRuleThreadSafety)
