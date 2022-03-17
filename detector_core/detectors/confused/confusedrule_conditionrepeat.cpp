#include "confusedrule_conditionrepeat.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"
#include "common/maphelp.h"
#include "detectorcommon/ifdefinition.h"

ConfusedRuleConditionRepeat::ConfusedRuleConditionRepeat() : Rule("ConfusedRuleConditionRepeat")
, m_ifDefinition(make_unique<IfDefinition>())
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        "Confusing judgment condition. The judgment condition already exists.",
        U8("令人迷惑的判断条件，判断条件重复"));
}

ConfusedRuleConditionRepeat::~ConfusedRuleConditionRepeat() = default;

bool ConfusedRuleConditionRepeat::detectCore(const string & code, const ErrorFile & errorFile)
{
    if (StringHelper(code).findCode("\\"))
    {
        //filter macro definition
        resetData();
        return false;
    }

    if (DetectorHelper::isFunctionDefinition(code))
    {
        m_conditions.clear();
    }

    if (!m_conditions.empty())
    {
        auto indexOfRightBrace = DetectorHelper::getIndexOfRightBrace(code);
        if (indexOfRightBrace != string::npos)
        {
            m_conditions = MapHelp<size_t>(m_conditions).erase(indexOfRightBrace, [](const size_t& element, const size_t& reference) {
                return reference < element; });
        }
    }

    for (const auto& item : m_conditionContexts)
    {
        //for (const auto& operand : item.operands)
        if (assignToOperand(code, item.operands.first)
            || assignToOperand(code, item.operands.second))
        {
            return false;
        }
    }

    if (!m_ifDefinition->inIfDefinition(code)
        || !m_ifDefinition->isEnd())
    {
        return false;
    }

    auto condition = m_ifDefinition->condition();
    m_conditionContexts = m_ifDefinition->getConditionContexts();
    auto countOfSpace = StringHelper(code).continuousCharactersFromStart(" ").size();
    if (m_conditions.find(condition) != m_conditions.end()
        && m_conditions[condition] == countOfSpace)
    {
        storeRuleError(errorFile);
        return true;
    }
    m_conditions.insert({ condition, countOfSpace });
    return false;
}

void ConfusedRuleConditionRepeat::resetData()
{
    Rule::resetData();
    m_ifDefinition->resetData();
    m_conditions.clear();
    m_conditionContexts.clear();
}

bool ConfusedRuleConditionRepeat::checkOperand(const string & condition, const string & operand)
{
    return StringHelper(condition).findIndexOfCode(operand) != string::npos;
}

bool ConfusedRuleConditionRepeat::assignToOperand(const string& code, const string& operand)
{
    if (operand.empty())
    {
        return false;
    }
    auto codeTmp = StringHelper(code).removeSpaceAndTab();
    if (codeTmp.find(operand + "=") != string::npos
        && codeTmp.find(operand + "==") == string::npos)
    {
        //if (PasswordSuccessful != result)
        //result = verifyNew(enteredNewPSD);
        //if (PasswordSuccessful != result)
        for (const auto& item1 : m_conditions)
        {
            auto condition = item1.first;

            if (checkOperand(condition, operand))
            {
                m_conditions.erase(condition);
                m_conditionContexts.clear();
                return true;
            }
        }
    }
    return false;
}
