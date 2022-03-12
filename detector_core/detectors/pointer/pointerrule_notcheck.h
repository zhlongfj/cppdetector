#pragma once
#include "../rule.h"
#include "common/reflecter.h"
#include "detector_global.h"

class DETECTOR_EXPORT PointerRuleNotCheck final : public Rule {
public:
    PointerRuleNotCheck();

    bool detectCore(const std::string& code, const ErrorFile& errorFile) override;

    void resetData() override;
private:
    struct PointerCheck
    {
        bool checked = false;
        bool inChecked = false;
    };
    std::pair<bool, bool> checkTernaryOperator(const string& code);
    bool storeRuleErrorFromNotCheckNames(const std::pair<std::string, PointerCheck>& item);
    bool getPointerFromIf(const string& code);
    bool endOfCondition(const string& code);

    std::map<std::string, PointerCheck> m_objNames;
    std::multimap<std::string, ErrorFile> m_notCheckNames;
    std::string m_sapceBeforeIf;
};

REGISTER_CLASS(PointerRuleNotCheck)
