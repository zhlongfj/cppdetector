#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"

class DETECTOR_EXPORT MemLeakRuleDestructor final : public Rule {
public:
    MemLeakRuleDestructor();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;
    
    void resetData() override;

private:
    bool  m_isStruct = false;
    std::string m_className;
    std::string m_spaceBeforeClass;
};

REGISTER_CLASS(MemLeakRuleDestructor)
