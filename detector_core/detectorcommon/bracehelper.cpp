#include <string>
#include "bracehelper.h"
#include "common/stringhelper.h"
#include "detectorhelp.h"
#include <iostream>
using namespace std;

int BraceHelper::calculateCountOfOpenBrace(const string& code, const int line)
{
    auto codeWithoutSpace = StringHelper(code).removeSpaceAndTab();

    bool atBegin = openBraceAtBegin(codeWithoutSpace);
    bool afterRightParenthesis = openBraceAfterCloseParenthesis(codeWithoutSpace);
    auto findLeftBrace = atBegin || afterRightParenthesis;
    if (findLeftBrace
        && !StringHelper(codeWithoutSpace).betweenEdge("{", "\""))
    {
        ++m_countOfOpenBrace;
        m_findOpenBrace = true;
    }


    if (closeBrace(codeWithoutSpace))
    {
        reduceCountOfOpenBrace(line);
    }

    return m_countOfOpenBrace;
}

void BraceHelper::resetData()
{
    m_countOfOpenBrace = 0;
    m_findOpenBrace = false;

}

bool BraceHelper::openBraceAfterCloseParenthesis(const string& codeWithoutSpace)
{
    string braceAfterRightParenthesis = "){";
    if (codeWithoutSpace.size() < 2)
    {
        return false;
    }

    auto index = codeWithoutSpace.rfind(braceAfterRightParenthesis);
    return index != string::npos;
}

bool BraceHelper::openBraceAtBegin(const string& codeWithoutSpace)
{
    auto index = codeWithoutSpace.find("{");
    if (index == string::npos)
    {
        return false;
    }

    return index == 0;
}

void BraceHelper::reduceCountOfOpenBrace(const int line)
{
    --m_countOfOpenBrace;
    if (m_countOfOpenBrace < 0)
    {
        auto msg = "warning: m_countOfLeftBrace is " + to_string(m_countOfOpenBrace) + " in line: " + to_string(line);
        std::cout << msg << std::endl;
        m_countOfOpenBrace = 0;
    }
}

bool BraceHelper::closeBrace(const string& codeWithoutSpace)
{
    auto index = codeWithoutSpace.find("}");
    if (index == string::npos)
    {
        return false;
    }
    
    bool findRightBrace = index == codeWithoutSpace.size() - 1;
    return findRightBrace && !StringHelper(codeWithoutSpace).betweenEdge("}", "\"");
}
