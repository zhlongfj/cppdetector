#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"

class ArrayRuleHelper;
class DETECTOR_EXPORT ArrayRuleIndexOutOfBoundsFromFunc final : public Rule {
public:
    ArrayRuleIndexOutOfBoundsFromFunc();
    explicit ArrayRuleIndexOutOfBoundsFromFunc(std::unique_ptr<ArrayRuleHelper> helper);

    ~ArrayRuleIndexOutOfBoundsFromFunc();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::multimap<std::string, std::pair<int, std::string>> m_arrays;
    std::unique_ptr<ArrayRuleHelper> m_helper;
    std::pair<std::string, std::string> m_nameIndexPair;
};

REGISTER_CLASS(ArrayRuleIndexOutOfBoundsFromFunc)
