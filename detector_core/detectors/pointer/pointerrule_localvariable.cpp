#include "pointerrule_localvariable.h"
#include "detectorcommon/detectorhelp.h"

PointerRuleLocalVariable::PointerRuleLocalVariable() : Rule("PointerRuleLocalVariable") {
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Critical, m_name,
                                             U8("函数返回局部变量的地址或引用"));
}

bool PointerRuleLocalVariable::detectCore(const string &code, const ErrorFile &errorFile) {
    if (DetectorHelper::isFunctionDefinition(code)) {
        m_bInFunction = true;
        m_localVariableType.clear();
        return false;
    }

    if (code.find("(") != string::npos
        && (code.find("&") != string::npos || code.find("*") != string::npos)) {
        //Performance optimization, filter mismatches
        if (auto ret = DetectorHelper::check(code, "(\\w+)\\s*[&*]\\s*\\w+\\("); !ret.empty()) {
            m_localVariableType = ret[1];
            return false;
        }
    }

    if (m_localVariableType.empty()) {
        return false;
    }

    if (auto ret = DetectorHelper::check(code, m_localVariableType + "\\s+(\\w+)"); !ret.empty()) {
        if (code.find("static ") == string::npos) {
            m_localVariable = ret[1];
        }
        return false;
    }

    if (m_localVariable.empty()) {
        return false;
    }

    if (code.find("return") == string::npos
        || code.find(m_localVariable) == string::npos) {
        return false;
    }

    storeRuleError(errorFile);
    return true;
}

void PointerRuleLocalVariable::resetData() {
    Rule::resetData();
    m_localVariableType.clear();
    m_localVariable.clear();
    m_bInFunction = false;
}

