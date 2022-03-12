#pragma once
#include <memory>
#include "../rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"
#include <map>

class ArrayRuleHelper;
class DETECTOR_EXPORT ArrayRuleIndexOutOfBounds final : public Rule {
public:
    ArrayRuleIndexOutOfBounds();
    explicit ArrayRuleIndexOutOfBounds(std::unique_ptr<ArrayRuleHelper> helper);

    ~ArrayRuleIndexOutOfBounds();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::unique_ptr<ArrayRuleHelper> m_helper;
    std::multimap<std::string, int> m_arrays;
};

REGISTER_CLASS(ArrayRuleIndexOutOfBounds)
