#include "uninitrule_var.h"
#include "uninitrule_helper.h"

UninitRuleVar::UninitRuleVar() : Rule("UninitRuleVar"),
                                 m_uninitRuleVarHelper(make_unique<UninitRuleVariableDefinitionHelper>()) {
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Error, m_name,
                                             U8("基础类型变量可能未初始化，请确认（变量声明与初始化尽量在同一个语句）"));
}

UninitRuleVar::~UninitRuleVar() = default;

bool UninitRuleVar::detectCore(const string &code, const ErrorFile &errorFile) {
    m_uninitRuleVarHelper->checkClass(code);
    if (code.find("int") == string::npos
        && code.find("unsigned ") == string::npos
        && code.find("long ") == string::npos
        && code.find("bool ") == string::npos
        && code.find("char ") == string::npos
        && code.find("byte ") == string::npos
        && code.find("size_t ") == string::npos) {
        return false;
    }
    if (auto ret = DetectorHelper::check(code,
                                         R"delimiter(^\s*(u*_*int(\d*_t)*|unsigned\s+\w+|long|bool|char|byte|size_t)\s+(\w+);)delimiter"); !ret.empty()) {
        //check "int32_t s;"
        //storeRuleError(errorFile);
        if (m_uninitRuleVarHelper->detectCore(errorFile, ret[3])) {
            storeRuleError(errorFile);
            return true;
        }
        return false;
    }

    return false;
}

void UninitRuleVar::resetData() {
    auto errorFiles = m_uninitRuleVarHelper->resetData();
    for (const auto &item: errorFiles) {
        storeRuleError(item);
    }
}
