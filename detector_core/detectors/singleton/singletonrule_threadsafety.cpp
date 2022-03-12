#include "singletonrule_threadsafety.h"
#include "detectorcommon/detectorhelp.h"

SingletonRuleThreadSafety::SingletonRuleThreadSafety() : Rule("SingletonRuleThreadSafety")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Error, m_name,
        U8("不是线程安全的"));
}

bool SingletonRuleThreadSafety::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (code.find("return") == string::npos
        && code.find("static") == string::npos
        && code.find("if") == string::npos)
    {
        return false;
    }

    if (m_className.empty())
    {
        if (auto ret = DetectorHelper::check(code, " *static *(\\w+) *\\* *get[Ii]nstance"); !ret.empty())
        {
            //check "static Test* getInstance();"
            m_errorFile = errorFile;
            m_className = ret[1];
        }
        return false;
    }

    if (m_parameterName.empty())
    {
        //regValue: " *static *Test *\* *(\w*);"
        if (auto ret = DetectorHelper::check(code, " *static *" + m_className + " *\\* *(\\w*);"); !ret.empty())
        {
            //check "static Test* m_tt;"
            m_parameterName = ret[1];
        }
        return false;
    }

    if (!m_findIf)
    {
        m_findIf = !DetectorHelper::check(code, "if *\\(.*" + m_parameterName + "\\)").empty();
        return false;
    }

    if (!DetectorHelper::check(code, "if *\\(" + m_parameterName + "\\)").empty())
    {
        clear();
        return false;
    }

    if (DetectorHelper::check(code, "return *" + m_parameterName).empty())
    {
        return false;
    }
    clear();
    storeRuleError(errorFile);
    return true;
}

void SingletonRuleThreadSafety::resetData()
{
    Rule::resetData();
    clear();
}

void SingletonRuleThreadSafety::clear()
{
    m_findIf = false;
    m_className.clear();
    m_parameterName.clear();
}

