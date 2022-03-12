#include "operationrule_float.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"

OperationRuleFloat::OperationRuleFloat() : Rule("OperationRuleFloat") {
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Error, m_name,
                                             U8("对浮点数或双精度数不能用相等或不相等来比较"));
}

bool OperationRuleFloat::detectCore(const string &code, const ErrorFile &errorFile) {
    auto code1 = StringHelper(code).toLower();

    auto name = DetectorHelper::getNameOfFunctionDefinition(code);
    if (!name.empty()) {
        m_funcName = name;
    }

    insertVarNames(code1);

    auto index = code1.find("}");
    if (index != string::npos) {
        auto spaceCount = code1.substr(0, index).size();
        if (spaceCount == 4) {
            m_funcName.clear();
            m_varNamesInFunc.clear();
            return false;
        }
    }

    if (m_varNames.empty() && m_varNamesInFunc.empty()) {
        return false;
    }

    if (code.find("if") == string::npos
        || code.find("=") == string::npos) {
        //Performance optimization, filter mismatches
        return false;
    }

    if (auto ret = DetectorHelper::check(code1, R"delimiter(if\s*\(\s*(\w+)\s*[!=]=\s*(\w+))delimiter"); !ret.empty()) {
        if (any_of(m_varNames.begin(), m_varNames.end(),
                   [this, &ret](const auto &item) { return checkVarName(item, ret[1].str(), ret[2].str()); })) {
            storeRuleError(errorFile);
            return true;
        }

        if (any_of(m_varNamesInFunc.begin(), m_varNamesInFunc.end(),
                   [this, &ret](const auto &item) { return checkVarName(item, ret[1].str(), ret[2].str()); })) {
            storeRuleError(errorFile);
            return true;
        }
    }

    return false;
}

bool OperationRuleFloat::insertVarNames(const string &code1) {
    if (code1.find("float ") == string::npos
        && code1.find("double ") == string::npos)
    {
        return false;
    }
    if (auto ret = DetectorHelper::check(code1, "(float|double)\\s+(\\w+)"); !ret.empty()) {
        if (m_funcName.empty()) {
            m_varNames.insert(ret[2]);
        } else {
            m_varNamesInFunc.insert(ret[2]);
        }
    }
    return true;
}

void OperationRuleFloat::resetData() {
    Rule::resetData();
    m_varNames.clear();
    m_varNamesInFunc.clear();
    m_funcName.clear();
}

bool OperationRuleFloat::checkVarName(const string &varName, const string &left, const string &right) {
    return varName == left || varName == right;
}

