#include "confusedrule_break.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"
#include "detectorcommon/bracehelper.h"

ConfusedRuleBreak::ConfusedRuleBreak() : Rule("ConfusedRuleBreak") 
    , m_braceHelper(make_unique<BraceHelper>())
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        "Confusing break. This may cause the loop to be executed only once.",
        U8("令人迷惑的break，可能导致循环只执行一遍"));
}

ConfusedRuleBreak::~ConfusedRuleBreak() = default;

bool ConfusedRuleBreak::detectCore(const string &code, const ErrorFile &errorFile) {

    if (code.find("for") != string::npos
        || code.find("while") != string::npos) {
        if (auto ret = DetectorHelper::check(code, "(for|while)\\s*\\("); !ret.empty()) {
            m_indexOfLoop = code.substr(0, code.find(ret[1]));
            return false;
        }
    }

    if (m_indexOfLoop.empty()) {
        return false;
    }

    auto indexOfSwitch = code.find("switch (");
    if (indexOfSwitch != string::npos) {
        m_indexOfSwitch = indexOfSwitch;
        m_countOfBraceInSwitch = m_braceHelper->calculateCountOfOpenBrace(code, errorFile.line);
    }

    if (m_indexOfSwitch != string::npos) {
        m_countOfBraceInSwitch = m_braceHelper->calculateCountOfOpenBrace(code, errorFile.line);
        if (m_countOfBraceInSwitch == 0
            && m_braceHelper->findOpenBrace()) {
            m_indexOfSwitch = string::npos;
            m_braceHelper->resetData();
        }
    }

    if (auto index = DetectorHelper::getIndexOfRightBrace(code); index == m_indexOfLoop.size()) {
        m_indexOfLoop.clear();
        return false;
    }

    if (code == m_indexOfLoop + "    break;") {
        if (m_indexOfSwitch != string::npos
            && m_countOfBraceInSwitch != 0) {
            return false;
        }
        storeRuleError(errorFile);
    }
    return true;
}

void ConfusedRuleBreak::resetData() {
    Rule::resetData();
    m_indexOfLoop.clear();
    m_indexOfSwitch = string::npos;
    m_countOfBraceInSwitch = 0;
}
