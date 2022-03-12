#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"

class DETECTOR_EXPORT OperationRuleBitwiseWithBool final : public Rule {
public:
    OperationRuleBitwiseWithBool();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:

    bool valid(const std::string& variableName, const std::string& path);

    std::string getRegValue(const std::string& variableName);
    std::string m_data;
};

REGISTER_CLASS(OperationRuleBitwiseWithBool)
