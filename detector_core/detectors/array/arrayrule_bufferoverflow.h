#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"

class ArrayRuleHelper;
class DETECTOR_EXPORT ArrayRuleBufferOverflow final : public Rule {
public:
    ArrayRuleBufferOverflow();
    explicit ArrayRuleBufferOverflow(std::unique_ptr<ArrayRuleHelper> helper);

    ~ArrayRuleBufferOverflow();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::unique_ptr<ArrayRuleHelper> m_helper;
    std::multimap<std::string, pair<int, std::string>> m_arrays;
};

REGISTER_CLASS(ArrayRuleBufferOverflow)
