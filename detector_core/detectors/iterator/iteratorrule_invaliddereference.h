#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"

class DETECTOR_EXPORT IteratorRuleInvalidDereference final : public Rule {
public:
    IteratorRuleInvalidDereference();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    bool checkReference(const string& code, const ErrorFile& errorFile);

    void resetData() override;

private:
    std::string m_iteratorName;
    std::string m_spaces;
};

REGISTER_CLASS(IteratorRuleInvalidDereference)
