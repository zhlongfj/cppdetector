#include "accesscontrolrule_membervariable.h"
#include "detectorcommon/detectorhelp.h"
#include "detectorcommon/functiondefinition.h"
#include "detectorcommon/classdefinition.h"
#include "detectorcommon/variabledefinition.h"

AccessControlRuleMemberVariable::AccessControlRuleMemberVariable() : Rule("AccessControlRuleMemberVariable")
    , classDefinition(make_unique<ClassDefinition>())
    , variableDefinition(make_unique<VariableDefinition>())
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        "Do not set the access to member variables to public.",
        U8("不要将成员变量访问权限设置成public"));
}

AccessControlRuleMemberVariable::~AccessControlRuleMemberVariable() = default;

bool AccessControlRuleMemberVariable::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (!classDefinition->inClassDefinition(code))
    {
        return false;
    }

    if (classDefinition->isStruct()
        || classDefinition->getAccessControl(code) != AccessControl::PUBLIC)
    {
        return false;
    }

    if (!variableDefinition->isVariableDefinition(code))
    {
        return false;
    }

    storeRuleError(errorFile);
    return true;
}

void AccessControlRuleMemberVariable::resetData()
{
    Rule::resetData();
    classDefinition->resetData();
}

