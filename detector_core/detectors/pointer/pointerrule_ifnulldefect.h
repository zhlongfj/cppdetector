#pragma once
#include "../rule.h"
#include "common/reflecter.h"
#include <string>

class DETECTOR_EXPORT PointerRuleIfNullDefect final : public Rule {
public:
    PointerRuleIfNullDefect();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::string m_objName;
    bool m_hasAnd = false;
};

REGISTER_CLASS(PointerRuleIfNullDefect)
