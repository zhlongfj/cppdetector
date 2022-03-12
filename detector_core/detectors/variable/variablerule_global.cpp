#include "detectorcommon/detectorhelp.h"
#include "detectorcommon/functiondefinition.h"
#include "detectorcommon/variabledefinition.h"
#include "detectorcommon/classdefinition.h"
#include "variablerule_global.h"

//Double free raised by a global or static variable
//https://joydig.com/research-global-variables-desctruction-behavior-in-cpp/

VariableRuleGlobal::VariableRuleGlobal() : Rule("VariableRuleGlobal")
    , m_functionDefinition(make_unique<FunctionDefinition>())
    , m_classDefinition(make_unique<ClassDefinition>())
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        U8("静态生存周期的对象（全局变量，静态变量，静态类成员变量），都必须是POD类型(constexpr除外)。"));
}

VariableRuleGlobal::~VariableRuleGlobal() = default;

bool VariableRuleGlobal::detectCore(const string& code, const ErrorFile& errorFile)
{
    VariableDefinition definition;
    bool isVariable = definition.isVariableDefinition(code);
    bool inFunction = m_functionDefinition->inFunctionDefinition(code);
    bool inClass = m_classDefinition->inClassDefinition(code);
    bool memberWithoutStatic = !definition.isStatic() && inClass && !inFunction;
    if (inFunction
        || definition.isConstexpr()
        || memberWithoutStatic)
    {
        return false;
    }

    if (!isVariable)
    {
        return false;
    }

    auto type = definition.type();
    if (type.find("shared") == 0
        || type.find("unique") == 0
        || type.find("std::shared") == 0
        || type.find("std::unique") == 0)
    {
        return false;
    }

    auto ret1 = DetectorHelper::check(type, "\\s*(u*int(\\d*_t)*|qint\\d*|unsigned\\s+\\w+|long|double|float|bool|char|byte|size_t|(std::)*(string|mutex|condition_variable))$");
    if (!ret1.empty())
    {
        return false;
    }

    storeRuleError(errorFile);
    return true;
}

void VariableRuleGlobal::resetData()
{
    Rule::resetData();
    m_functionDefinition->resetData();
    m_classDefinition->resetData();
}
