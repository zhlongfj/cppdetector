#include "pointerrule_returnnull.h"
#include "detectorcommon/detectorhelp.h"
#include "../../detectorcommon/detectorcommon.h"

PointerRuleReturnNull::PointerRuleReturnNull() : Rule("PointerRuleReturnNull") {
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Critical, m_name,
        U8("函数返回值可能为空，请先判空再使用"));
}

bool PointerRuleReturnNull::detectCore(const string& code, const ErrorFile& errorFile) {
    if (auto ret = DetectorHelper::getNameOfFunctionDefinition(code); !ret.empty()) {
        //check "int* DemoFunc()"
        m_funcName = ret;
        m_returnNulls.insert({ ret, make_shared<ReturnNull>() });
        return false;
    }

    if (m_returnNulls.empty()) {
        return false;
    }

    if (StringHelper(code).isReturnNull()) {
        m_returnNulls[m_funcName]->mayNULL = true;
        return false;
    }

    if (insertReturnNull(code, errorFile))
    {
        return false;
    }

    return conditionWithNull(code);
}

bool PointerRuleReturnNull::insertReturnNull(const string& code, const ErrorFile& errorFile) {
    if (code.find("=") == string::npos)
    {
        //Performance optimization, filter mismatches
        return false;
    }

    auto regValue = R"delimiter((\w+)\s+=\s+(\w+::)*(\w+)\s*\()delimiter";
    auto ret = DetectorHelper::check(code, regValue);
    if (ret.empty())
    {
        return false;
    }

    if (any_of(m_returnNulls.begin(), m_returnNulls.end(), [&ret](const auto& item) {
        return item.first == ret[3].str();
        })) {
        //check "int* p = DemoFunc();"
        m_returnNulls[ret[3]]->vars.insert({ ret[1], errorFile });
        return true;
    }

    return false;
}

bool PointerRuleReturnNull::conditionWithNull(const string& code) {
    if (code.find("if") == string::npos
        || code.find("=") == string::npos) {
        return false;
    }
    if (auto ret = DetectorHelper::check(code, "if\\s*\\((\\w+)\\s*[!=]=\\s*(\\w+)"); !ret.empty()) {
        //check "if(p == nullptr"
        string var;
        for (const auto& item : m_returnNulls) {
            auto& vars = item.second->vars;
            if (vars.empty()) {
                continue;
            }
            if (vars.find(ret[1]) != vars.end()) {
                var = ret[1];
            }
            else if (vars.find(ret[2]) != vars.end()) {
                var = ret[2];
            }
            auto iter = vars.find(var);
            if (!var.empty()
                && iter != vars.end()) {
                auto count = vars.count(var) - 1;
                while (count) {
                    ++iter;
                    count--;
                }
                vars.erase(iter);
            }
        }
    }
    return false;
}

void PointerRuleReturnNull::resetData() {
    Rule::resetData();
    for (const auto& item : m_returnNulls) {
        for (const auto& item1 : item.second->vars) {
            if (item.second->mayNULL)
            {
                storeRuleError(item1.second);
            }
        }
    }
    m_funcName.clear();
    m_returnNulls.clear();
}

