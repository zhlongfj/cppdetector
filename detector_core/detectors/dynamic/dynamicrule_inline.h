#pragma once
#include "../rule.h"
#include "common/reflecter.h"
#include "detector_global.h"

struct ErrorFileWithClass {
    std::vector<std::string> classNames;
    ErrorFile errorFile;
};

class DETECTOR_EXPORT DynamicRuleInline final : public Rule {
public:
    DynamicRuleInline();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    bool findClassDomain(const std::string& code, const std::vector<std::string>& classNames);
    
    void resetData() override;

private:
    map<std::string, ErrorFileWithClass> m_errorFileWithClass;
};

REGISTER_CLASS(DynamicRuleInline)
