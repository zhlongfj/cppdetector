#include "ifdefinition.h"
using namespace std;

bool IfDefinition::inIfDefinition(const string& content)
{
    if (m_isEnd)
    {
        resetData();
    }

    StringHelper helper(content);
    helper.removeEndSpaceAndTab();
    if (!m_inDefinition)
    {
        if (!helper.findCode("if"))
        {
            return false;
        }

        m_inDefinition = true;
        
        string charBeforeCondition = ";";
        auto index = helper.findIndexOfCode(";");
        if (index == string::npos)
        {
            charBeforeCondition = "(";
        }
        if (auto ret = helper.content().find(charBeforeCondition); ret != string::npos)
        {
            handleCondition(helper.content(), ret + 1);
            return true;
        }
    }

    handleCondition(helper.content(), 0);
    return true;
}

void IfDefinition::resetData()
{
    m_condition.clear();
    m_conditionContexts.clear();
    m_isEnd = false;
    m_inDefinition = false;
}

std::size_t IfDefinition::findEnd(const string& content)
{
    auto indexOfEnd = content.rfind(")");
    if (indexOfEnd != string::npos)
    {
        StringHelper helper(content);
        if (indexOfEnd == content.size() - 1
            && helper.count('(') <= helper.count(')'))
        {
            m_isEnd = true;
        }
        else
        {
            indexOfEnd = string::npos;
        }
    }
    return indexOfEnd;
}

void IfDefinition::handleCondition(const string& content, const size_t& indexOfStart)
{
    auto indexOfEnd = findEnd(content);
    auto condition = content.substr(indexOfStart, indexOfEnd - indexOfStart);
    addCondition(condition);
    if (m_isEnd)
    {
        auto condition = m_condition;
        auto localOperator = getLocalOperator(condition);
        while (!localOperator.first.empty())
        {
            generateIfConfition(condition, localOperator);
            localOperator = getLocalOperator(condition);
        }
        generateIfConfition(condition, localOperator);

        for (auto& element : m_conditionContexts)
        {
            StringHelper helper(element.conditionExpresss);
            helper.remove("(");
            helper.remove(")");
            auto content = helper.content();
            auto ret = DetectorHelper::check(content, R"delimiter((\w+)([!<>=]=?)(.+))delimiter");
            if (ret.empty())
            {
                element.operands.first = content;
                if (content[0] == '!')
                {
                    element.operatorName = '!';
                    element.operands.first = content.substr(1);
                }
                continue;
            }
            element.operatorName = ret[2];
            element.operands.first = ret.prefix().str() + ret[1].str();
            element.operands.second = ret[3].str() + ret.suffix().str();
        }
    }
}

void IfDefinition::addCondition(const string& content)
{
    auto condition = StringHelper(content).removeSpaceAndTab();
    m_condition += condition;
}

std::pair<std::string, std::size_t> IfDefinition::getLocalOperator(std::string& condition)
{
    auto localOperator = "&&";
    if (auto index = condition.find(localOperator); index != string::npos)
    {
        return { localOperator, index };
    }

    localOperator = "||";
    if (auto index = condition.find(localOperator); index != string::npos)
    {
        return { localOperator, index };
    }

    return { "", string::npos };
}

void IfDefinition::generateIfConfition(std::string& condition, const std::pair<std::string, std::size_t>& localOperator)
{
    ConditionContext conditionContext;
    conditionContext.conditionExpresss = condition.substr(0, localOperator.second);
    conditionContext.logicalOperatorToNext = localOperator.first;
    if (!localOperator.first.empty())
    {
        condition = condition.substr(localOperator.second + localOperator.first.size());
    }
    m_conditionContexts.push_back(conditionContext);
}
