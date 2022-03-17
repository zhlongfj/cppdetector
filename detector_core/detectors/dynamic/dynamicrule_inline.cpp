#include "dynamicdetector.h"
#include "detectorcommon/detectorhelp.h"
#include "dynamicrulehelper.h"

DynamicRuleInline::DynamicRuleInline() : Rule("DynamicRuleInline")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Error, m_name,
        "All members within the parent and child classes are implemented in header files. When when a safe conversion (dynamatic_cast) is performed outside the dynamic library, android5.1 will fail to convert.",
        U8("父类和子类所有成员都在头文件实现，在动态库外，进行安全转换（dynamatic_cast）时, android5.1会转换失败"));
}

bool DynamicRuleInline::detectCore(const string& code, const ErrorFile& errorFile)
{
    auto ret = DynamicRuleHelper::findExportedClass(code);
    if (!ret.second.empty())
    {
        //There is an inheritance relationship
        m_errorFileWithClass.insert({ ret.first, ErrorFileWithClass{{ret.first, ret.second}, errorFile} });
        return false;
    }

    if (!ret.first.empty())
    {
        //Class definition or declaration, but There is no inheritance
        return false;
    }

    auto iter = find_if(m_errorFileWithClass.begin(), m_errorFileWithClass.end(), [&code, this](const auto& item) {return findClassDomain(code, item.second.classNames); });
    if (iter != m_errorFileWithClass.end())
    {
        m_errorFileWithClass.erase(iter);
    }

    return false;
}

bool DynamicRuleInline::findClassDomain(const std::string& code, const vector<string>& classNames)
{
    return any_of(classNames.begin(), classNames.end(), [&code](const auto& item) {return DynamicRuleHelper::findClassDomain(code, item); });
}

void DynamicRuleInline::resetData()
{
    Rule::resetData();
    for (const auto& item : m_errorFileWithClass)
    {
        storeRuleError(item.second.errorFile);
    }
    m_errorFileWithClass.clear();
}

