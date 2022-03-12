#pragma once
#include "detectors/detector.h"
#include "../rule.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/reflecter.h"

#include <cctype>
#include "../../common/stringhelper.h"

class OperationRuleArithmeticWithBool final : public Rule {
public:
    OperationRuleArithmeticWithBool();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::set<std::string> m_varNames;
};

REGISTER_CLASS(OperationRuleArithmeticWithBool)
