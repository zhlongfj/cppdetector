#pragma once
#include "../rule.h"
#include "common/reflecter.h"

struct ReturnNull
{
    bool mayNULL = false;
    std::multimap<std::string, ErrorFile> vars;
};

class PointerRuleReturnNull final : public Rule {
public:
    PointerRuleReturnNull();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::string m_funcName;
    std::map<std::string, shared_ptr<ReturnNull>> m_returnNulls;

    bool conditionWithNull(const string &code);

    bool insertReturnNull(const string &code, const ErrorFile &errorFile);
};

REGISTER_CLASS(PointerRuleReturnNull)
