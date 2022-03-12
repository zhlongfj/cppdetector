#include "sizeofrule_pointer.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"
#include "detectorcommon/variabledefinition.h"

SizeOfRulePointer::SizeOfRulePointer() : Rule("SizeOfRulePointer")
, m_variableDefinition(make_unique<VariableDefinition>())
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        U8("对指针使用sizeof，请确认是否正确"));
}

SizeOfRulePointer::~SizeOfRulePointer() = default;

bool SizeOfRulePointer::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (m_variableDefinition->isVariableDefinition(code))
    {
        if (m_variableDefinition->isPoint()
            || m_variableDefinition->isPointToPoint())
        {
            m_variableNames.emplace(m_variableDefinition->name());
            return false;
        }
        return false;
    }

    if (!StringHelper(code).findCode("sizeof"))
    {
        return false;
    }

    auto ret = DetectorHelper::check(code, "sizeof\\s*\\(\\s*(\\w+)");
    if (ret.empty())
    {
        return false;
    }

    if (m_variableNames.find(ret[1]) == m_variableNames.end())
    {
        return false;
    }

    storeRuleError(errorFile);
    return true;
}

void SizeOfRulePointer::resetData()
{
    Rule::resetData();
    m_variableNames.clear();
}

