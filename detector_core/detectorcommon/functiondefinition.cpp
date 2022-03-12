#include "functiondefinition.h"
using namespace std;

bool FunctionDefinition::inFunctionDefinition(const string& content)
{
    auto spaceBeforeContent = StringHelper(content).continuousCharactersFromStart(" ");
    if (isFunctionDefinition(content))
    {
        m_sapceBeforeFunction = spaceBeforeContent;
        m_sapceBeforeFunctions.emplace_back(m_sapceBeforeFunction);
        auto contentWithoutSpace = StringHelper(content).removeSpaceAndTab();
        m_inFunction = !(contentWithoutSpace.rfind("}") == contentWithoutSpace.size() - 1);
        return m_inFunction;
    }

    if (m_inFunction && content.find("}") != string::npos)
    {
        if (spaceBeforeContent == m_sapceBeforeFunction)
        {
            m_sapceBeforeFunctions.pop_back();
            m_sapceBeforeFunction.clear();
            m_inFunction = false;
            if (!m_sapceBeforeFunctions.empty())
            {
                m_sapceBeforeFunction = m_sapceBeforeFunctions.back();
                m_inFunction = true;
            }

            return true;
        }
    }

    return m_inFunction;
}

bool FunctionDefinition::isFunctionDefinition(const string& content)
{
    auto ret = DetectorHelper::getNameOfFunctionDefinition(content);
    if (ret.empty())
    {
        return false;
    }

    m_funcName = ret;
    m_returnType = StringHelper(content.substr(0, content.find(ret))).removeSpaceAndTab();
    return true;
}

void FunctionDefinition::resetData()
{
    m_sapceBeforeFunction.clear();
    m_sapceBeforeFunction.clear();
    m_funcName.clear();
    m_returnType.clear();
    m_inFunction = false;
}

