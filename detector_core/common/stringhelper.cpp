//
// Created by Hualong Zhang on 2021/4/27.
//

#include <fstream>
#include <iostream>
#include "stringhelper.h"
#include <sstream>
#include <iosfwd>
#include <regex>

using namespace std;

std::vector<std::string> StringHelper::getLines()
{
    std::istringstream iStream(m_content);
    std::string line;

    std::vector<std::string> lines;
    while (std::getline(iStream, line)) {
        lines.emplace_back(line);
    }
    return lines;
}

std::vector<std::string> StringHelper::split(const std::string& delims)
{
    std::regex reg(delims);

    std::sregex_token_iterator p(m_content.begin(), m_content.end(), reg, -1);
    std::sregex_token_iterator end;
    std::vector<std::string> vec;
    while (p != end)
        vec.emplace_back(*p++);

    return vec;
}

bool StringHelper::isDigit()
{
    for (const auto& item : m_content)
    {
        if (!isdigit(item))
        {
            return false;
        }
    }
    return true;
}

string StringHelper::replace(const string& source, const string& target)
{
    auto& content = m_content;
    while (content.rfind(source) != string::npos)
    {
        content.replace(content.rfind(source), source.size(), target);
    }
    return content;
}

string StringHelper::removeSpaceAndTab()
{
    auto& str = m_content;
    str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char x) {return std::isspace(x) || x == '\t'; }), str.end());
    return str;
}

string StringHelper::removeBeginSpaceAndTab()
{
    if (m_content[0] != ' ')
    {
        return m_content;
    }
    auto& str = m_content;
    size_t index = 0;
    while (str[index] == ' ' || str[index] == '\t')
    {
        ++index;
    }
    str = str.substr(index);
    return str;
}

string StringHelper::removeEndSpaceAndTab()
{
    size_t index = m_content.size() - 1;
    if (m_content.empty()
        || m_content[index] != ' '
        && m_content[index] != '\t')
    {
        return m_content;
    }
    auto& str = m_content;
    while (str[index] == ' ' || str[index] == '\t')
    {
        if (index == 0)
        {
            break;
        }
        --index;
    }
    str = str.substr(0, index + 1);
    return str;
}

std::string StringHelper::trim()
{
    removeBeginSpaceAndTab();
    removeEndSpaceAndTab();
    return m_content;
}

std::string StringHelper::toLower()
{
    for (auto& item : m_content)
    {
        item = tolower(item);
    }
    return m_content;
}

std::string StringHelper::continuousCharactersFromStart(const string& characters)
{
    auto contentTmp = m_content;
    string result;
    while (true)
    {
        auto index = contentTmp.find(characters);
        if (index == string::npos
            || index > 0)
        {
            return result;
        }
        result += characters;
        contentTmp = contentTmp.substr(index + 1);
    }
    return result;
}

std::string StringHelper::removeFromStart(const string& characters)
{
    auto index = m_content.find(characters);
    if (index == string::npos)
    {
        return m_content;
    }

    return m_content.substr(index + characters.size());
}

bool StringHelper::remove(const string& target)
{
    auto index = m_content.find(target);
    if (index == string::npos)
    {
        return false;
    }
    m_content.erase(index, target.size());
    return true;
}

bool StringHelper::findCode(const string& target)
{
    auto index = m_content.find(target);
    if (index == string::npos)
    {
        return false;
    }

    auto left = m_content.find("\"");
    auto right = m_content.rfind("\"");
    if (left != string::npos
        && right != string::npos)
    {
        if (left < index
            && right > index)
        {
            return false;
        }
    }

    if (index > 0)
    {
        string leftIner = "\t. =!({)";
        //')' for (char*)realloc(buf, 100)
        if (leftIner.find(m_content[index - 1]) == string::npos)
        {
            return false;
        }
    }

    if (auto postfix = index + target.size(); postfix < m_content.size())
    {
        string rightIner = " .!=()};";
        //'.' for ret1.empty()
        if (rightIner.find(m_content[postfix]) == string::npos)
        {
            return false;
        }
    }

    return true;
}

bool StringHelper::isNull()
{
    return m_content == "NULL" || m_content == "nullptr";
}

bool StringHelper::betweenEdge(const string& target, const string& edge)
{
    auto index = m_content.find(edge);
    if (index == string::npos)
    {
        return false;
    }

    auto indexOfTarget = m_content.find(target, index + edge.size());
    if (indexOfTarget == string::npos)
    {
        return false;
    }

    return m_content.find(edge, indexOfTarget + target.size()) != string::npos;
}

bool StringHelper::isReturnNull() {
    if (m_content.find("return nullptr;") == string::npos
        && m_content.find("return NULL;") == string::npos)
    {
        return false;
    }
    return true;
}

size_t StringHelper::getIndexAfterTarget(const string& target) {
    auto index = m_content.find(target);
    if (index == string::npos)
    {
        return string::npos;
    }

    return index + target.size();
}

std::string StringHelper::getVariableFromSelfOperation(const string& selfOperation)
{
    auto index = m_content.find(selfOperation);
    if (index == string::npos)
    {
        return "";
    }

    if (index == 0)
    {
        return m_content.substr(selfOperation.size());
    }
    return m_content.substr(0, index);
}

size_t StringHelper::count(const char& target)
{
    return std::count_if(m_content.begin(), m_content.end(), [target](const auto& element) {
        return element == target;
        });
}

size_t StringHelper::findIndexOfCode(const string& target)
{
    if (betweenEdge(target, "\""))
    {
        return string::npos;
    }

    return m_content.find(target);
}
