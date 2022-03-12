#pragma once
#include "../rule.h"
#include "common/reflecter.h"
#include <memory>
#include "detector_global.h"

class ArrayRuleHelper;
class DETECTOR_EXPORT ArrayRuleIndexOutOfBoundsInLoop final : public Rule {
public:
    ArrayRuleIndexOutOfBoundsInLoop();
    explicit ArrayRuleIndexOutOfBoundsInLoop(std::unique_ptr<ArrayRuleHelper> helper);
    ~ArrayRuleIndexOutOfBoundsInLoop();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::unique_ptr<ArrayRuleHelper> m_helper;
    std::multimap<std::string, pair<int, std::string>> m_arrays;
    std::string m_maxLenInLoop;
};

REGISTER_CLASS(ArrayRuleIndexOutOfBoundsInLoop)
