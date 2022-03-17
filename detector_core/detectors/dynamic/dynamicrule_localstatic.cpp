#include "dynamicrule_localstatic.h"
#include "dynamicrulehelper.h"
#include "detectorcommon/detectorhelp.h"

DynamicRuleLocalStatic::DynamicRuleLocalStatic() : Rule("DynamicRuleLocalStatic")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Error, m_name,
        "Local static variables may be used outside the dynamic library. When Android5.1 accesses across so, different so will instantiate an independent singleton, resulting in multiple instances in the system.",
        U8("可能在动态库外面使用的局部静态变量, Android5.1跨so访问时，不同so会实例化一份独立的单例，导致系统存在多实例"));
}

bool DynamicRuleLocalStatic::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (m_className.empty())
    {
        auto ret = DynamicRuleHelper::findExportedClass(code);
        if (!ret.first.empty())
        {
            m_className = ret.first;
        }
        return false;
    }

    //check "static Test2 test;
    if (code.find("static " + m_className + " ") == string::npos)
        //if (DetectorHelper::check(code, "static\\s+" + m_className + "\\s+(\\w+);").empty())
    {
        return false;
    }
    m_className.clear();
    storeRuleError(errorFile);
    return true;
}

void DynamicRuleLocalStatic::resetData()
{
    Rule::resetData();
    m_className.clear();
}

