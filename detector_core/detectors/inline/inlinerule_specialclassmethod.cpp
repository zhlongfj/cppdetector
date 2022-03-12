#include "inlinerule_specialclassmethod.h"
#include "detectorcommon/classdefinition.h"

InlineRuleSpecialClassMethod::InlineRuleSpecialClassMethod() : Rule("InlineRuleSpecialClassMethod")
    , classDefinition(make_unique<ClassDefinition>())
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Suggest, m_name,
        U8("不要将特殊的类方法设置为内联：构造函数，析构函数，虚函数"));
}

InlineRuleSpecialClassMethod::~InlineRuleSpecialClassMethod() = default;

bool InlineRuleSpecialClassMethod::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (errorFile.path.find(".h") == string::npos)
    {
        return false;
    }

    if (!classDefinition->inClassDefinition(code))
    {
        return false;
    }

    if (code.find("inline ") == string::npos)
    {
        return false;
    }

    if (!classDefinition->isConstructor(code).first
        && !classDefinition->isDestructor(code).first
        && !classDefinition->isVirtual(code))
    {
        return false;
    }

    storeRuleError(errorFile);
    return true;
}

void InlineRuleSpecialClassMethod::resetData()
{
    classDefinition->resetData();
    Rule::resetData();
}
