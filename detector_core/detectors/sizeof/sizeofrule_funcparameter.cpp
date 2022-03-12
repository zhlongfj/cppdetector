#include "sizeofrule_funcparameter.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"

SizeOfRuleFuncParameter::SizeOfRuleFuncParameter() : Rule("SizeOfRuleFuncParameter")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Error, m_name,
        U8("数组作为函数参数，在函数内对数组变量使用sizeof获取数组占用空间大小，但是数组参数本质上是指针，返回的是指针大小，即32位下是4，64位下是8"));
}

bool SizeOfRuleFuncParameter::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (code.find("[") != string::npos)
    {
        if (auto ret = DetectorHelper::check(code, R"delimiter(\w+\s+\w+\(.+\s+(\w+)\[\w*\])delimiter"); !ret.empty())
        {
            //check "int SizeOfRuleFuncParameterDemo1(int32_t sz[3])"
            m_arrayName = ret[1];
            return false;
        }
    }

    if (code.find("sizeof(" + m_arrayName + ")") != string::npos)
    {
        storeRuleError(errorFile);
        return true;
    }

    if (DetectorHelper::isFunctionDefinition(code))
    {
        m_arrayName.clear();
    }
    return false;
}

void SizeOfRuleFuncParameter::resetData()
{
    Rule::resetData();
    m_arrayName.clear();
}

