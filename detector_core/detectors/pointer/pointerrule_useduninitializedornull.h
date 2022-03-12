#pragma once
#include "../rule.h"
#include "detector_global.h"

class DETECTOR_EXPORT PointerRuleUsedUninitializedOrNull : public Rule {
public:
    using Rule::Rule;
    virtual ~PointerRuleUsedUninitializedOrNull() = default;
    bool detectReal(const std::string& code, const ErrorFile& errorFile, const std::string& objName);

    void resetData() override;

private:
    std::map<std::string, bool> m_objNames;
};