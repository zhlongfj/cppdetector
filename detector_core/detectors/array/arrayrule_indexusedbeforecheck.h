#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"
#include <memory>

class ArrayRuleHelper;
class DETECTOR_EXPORT ArrayRuleIndexUsedBeforeCheck final : public Rule {
public:
    ArrayRuleIndexUsedBeforeCheck();
    explicit ArrayRuleIndexUsedBeforeCheck(std::unique_ptr<ArrayRuleHelper> helper);
    ~ArrayRuleIndexUsedBeforeCheck();
    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::unique_ptr<ArrayRuleHelper> m_helper;
    std::string m_data;
    std::string m_target;
    bool m_needCheck = true;
};

REGISTER_CLASS(ArrayRuleIndexUsedBeforeCheck)
