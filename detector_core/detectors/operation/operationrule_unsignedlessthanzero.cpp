#include "operationrule_unsignedlessthanzero.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"

OperationRuleUnsignedLessThanZero::OperationRuleUnsignedLessThanZero() : Rule("OperationRuleUnsignedLessThanZero") {
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Error, m_name,
                                             U8("无符号数判断小于0，结果恒为false"));
}

bool OperationRuleUnsignedLessThanZero::detectCore(const string &code, const ErrorFile &errorFile) {
    if (code.find("u_int") != string::npos
        || code.find("uint") != string::npos
        || code.find("unsigned ") != string::npos
        || code.find("size_t ") != string::npos) {
        //Performance optimization, filter mismatches
        if (auto ret = DetectorHelper::check(code,
                                             "(u_*int(\\d*_t)*|(unsigned\\s+\\w+)|size_t)\\s+(\\w+)"); !ret.empty()) {
            m_varNames.insert(ret[4]);
            return false;
        }
    }

    if (m_varNames.empty() || code.find("0") == string::npos) {
        return false;
    }

    if (code.find("if") != string::npos
        && (code.find("<") != string::npos || code.find(">") != string::npos)) {
        //Performance optimization, filter mismatches
        if (auto ret = DetectorHelper::check(code, "if\\s*\\(\\s*(\\w+)\\s*([<>])=*\\s*(\\w+)"); !ret.empty()) {
            //check "if (i < 0)"
            if (ret[1] == "0" && ret[2] == ">"
                || ret[3] == "0" && ret[2] == "<") {
                if (m_varNames.find(ret[1]) != m_varNames.end()
                    || m_varNames.find(ret[3]) != m_varNames.end()) {
                    storeRuleError(errorFile);
                    return true;
                }
            }
        }
    }
    return false;
}

void OperationRuleUnsignedLessThanZero::resetData() {
    Rule::resetData();
    m_varNames.clear();
}

