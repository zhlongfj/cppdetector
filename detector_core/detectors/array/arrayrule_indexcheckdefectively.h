#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"
#include "detector_global.h"

struct ArrayLen
{
    string lenName;
};

class ArrayRuleHelper;
class DETECTOR_EXPORT ArrayRuleIndexCheckDefectively final : public Rule {
public:
    ArrayRuleIndexCheckDefectively();
    explicit ArrayRuleIndexCheckDefectively(std::unique_ptr<ArrayRuleHelper> helper);

    ~ArrayRuleIndexCheckDefectively();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;

private:
    std::multimap<std::string, pair<int, std::string>> m_arrays;
    std::unique_ptr<ArrayRuleHelper> m_helper;
    std::string m_dataRest;
    std::string m_checkStatement;
    std::vector<std::string> m_indexAndLen;;
    bool m_findCheck = true;
};

REGISTER_CLASS(ArrayRuleIndexCheckDefectively)
