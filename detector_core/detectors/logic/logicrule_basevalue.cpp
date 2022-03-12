#include "logicrule_basevalue.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"

LogicRuleBaseValue::LogicRuleBaseValue() : Rule("LogicRuleBaseValue") {
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
                                             U8("总是为真或为假的判断条件"));
}

bool LogicRuleBaseValue::detectCore(const string &code, const ErrorFile &errorFile) {
    if (code.find("if (1)") != string::npos
        || code.find("if (0)") != string::npos
        || code.find("if (true)") != string::npos
        || code.find("if (false)") != string::npos
            ) {
        storeRuleError(errorFile);
        return true;
    }
    return false;
}

void LogicRuleBaseValue::resetData() {
    Rule::resetData();
}

