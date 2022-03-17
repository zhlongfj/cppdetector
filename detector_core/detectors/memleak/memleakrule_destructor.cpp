#include "memleakrule_destructor.h"
#include "detectorcommon/detectorhelp.h"

MemLeakRuleDestructor::MemLeakRuleDestructor() : Rule("MemLeakRuleDestructor")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        "If the class cannot be inherited, please modify the class with final; "\
        "If the class can be inherited, please modify the destructor with virtual. "\
        "Otherwise, when the base class pointer is deleted, the destructor of the child class will not called, which may cause memory leaks.",
        U8("如果class不会被继承，请用final修饰class；如果class会被继承，请用virtual修饰析构函数，否则delete基类指针时，不会调用子类的析构函数可能导致内存泄漏"));
}

bool MemLeakRuleDestructor::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (auto className = DetectorHelper::checkClassDefinition(code); !className.empty())
    {
        if (code.find("struct ") != string::npos)
        {
            m_isStruct = true;
        }
        m_className = className;
        m_spaceBeforeClass = StringHelper(code).continuousCharactersFromStart(" ");
        auto codeTmp = StringHelper(code).removeSpaceAndTab();
        auto index = codeTmp.find(className);
        auto indexOfFinal = codeTmp.find("final");
        if (indexOfFinal != string::npos
            && indexOfFinal == index + className.size())
        {
            resetData();
        }
        return false;
    }

    if (m_className.empty()
        || m_isStruct)
    {
        return false;
    }

    if (auto ret = DetectorHelper::checkDestructor(code); !ret.empty())
    {
        if (code.find("virtual") != string::npos)
        {
            resetData();
            return false;
        }
        storeRuleError(errorFile);
        resetData();
        return true;
    }

    bool endOfClass = false;
    if (code.find("};") != string::npos
        && !DetectorHelper::check(code, "^\\s*\\};\\s*").empty())
    {
        if (m_spaceBeforeClass == StringHelper(code).continuousCharactersFromStart(" ")
            && !m_className.empty())
        {
            endOfClass = true;
            resetData();
        }
    }

    if (!endOfClass)
    {
        return false;
    }
    storeRuleError(errorFile);
    resetData();
    return true;
}

void MemLeakRuleDestructor::resetData()
{
    Rule::resetData();
    m_isStruct = false;
    m_className.clear();
    m_spaceBeforeClass.clear();
}

