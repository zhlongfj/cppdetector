#include "uninitrule_pointer.h"
#include "uninitrule_helper.h"
#include "detectorcommon/variabledefinition.h"

UninitRulePointer::UninitRulePointer() : Rule("UninitRulePointer")
    , m_uninitRuleVarHelper(make_unique<UninitRuleVariableDefinitionHelper>())
    , m_definition(make_unique<VariableDefinition>())
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        U8("指针未初始化，请确认（变量声明与初始化尽量在同一个语句）"));
}

UninitRulePointer::~UninitRulePointer() = default;

bool UninitRulePointer::detectCore(const string& code, const ErrorFile& errorFile)
{
    m_uninitRuleVarHelper->checkClass(code);
    if (!m_definition->isVariableDefinition(code)
        || m_definition->isStatic())
    {
        return false;
    }

    if (!m_definition->isPoint()
        && !m_definition->isPointToPoint())
    {
        return false;
    }

    if (m_definition->isInitialized())
    {
        return false;
    }

    storeRuleError(errorFile);
    return true;
    if (auto ret = DetectorHelper::check(code, "(\\w+::)*(\\w+)\\s*\\*\\s*(\\w+);"); !ret.empty())
    {
        if (ret[2] == "return")
        {
            //return *qxt_p_ptr;
            return false;
        }
        //check "Foo* p;"
        if (DetectorHelper::check(ret.prefix().str(), "\\w+").empty())
        {
            if (m_uninitRuleVarHelper->detectCore(errorFile, ret[3]))
            {
                storeRuleError(errorFile);
                return true;
            }
        }
    }

    return false;
}

void UninitRulePointer::resetData()
{
    auto errorFiles = m_uninitRuleVarHelper->resetData();
    for (const auto& item : errorFiles)
    {
        storeRuleError(item);
    }
}
