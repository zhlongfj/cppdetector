#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"

class OperationRuleFloat final : public Rule {
public:
    OperationRuleFloat();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:

    bool checkVarName(const std::string& varName, const std::string& left, const std::string& right);

    std::set<std::string> m_varNames;
    std::set<std::string> m_varNamesInFunc;
    std::string m_funcName;

    bool insertVarNames(const string &code1);
};

REGISTER_CLASS(OperationRuleFloat)
