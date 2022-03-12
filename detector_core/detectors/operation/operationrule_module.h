#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
class StringHelp;
class OperationRuleModule final : public Rule {
public:
    OperationRuleModule();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    bool invalid(const std::string& str1, const std::string& str2);

    int getModule(const std::string& str);
};

REGISTER_CLASS(OperationRuleModule)
