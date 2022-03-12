#include "codefilter.h"
#include "common/stringhelper.h"
using namespace std;

std::string CodeFilter::filterCode(const std::string& content)
{
    auto code = StringHelper(content).replace("\t", "    ");
    if (invalidCode(code))
    {
        return "";
    }

    code = removeComment(code);
    return StringHelper(code).removeEndSpaceAndTab();
}

bool CodeFilter::invalidCode(const string& content)
{
    auto contentTmp = StringHelper(content).removeSpaceAndTab();
    if (contentTmp.empty())
    {
        return true;
    }

    auto index = contentTmp.find("#");
    if (index == 0
        || index == 3)
    {
        //文件开头前3个字节有可能时不可见字符
        return true;
    }

    //         if (contentTmp.find("using") == 0
    //             || contentTmp.find("namespace") == 0)
    //         {
    //             //暂时只有variabledefinition需要过滤
    //             return true;
    //         }
    return isComment(contentTmp);
}

bool CodeFilter::isComment(const string& content)
{
    auto index = content.find("/*");
    if (index != string::npos
        && !m_inComment)
    {
        m_inComment = true;

        if (content.find("*/") != string::npos)
        {
            m_inComment = false;
        }
        return true;
    }
    else if (content.find("*/") != string::npos)
    {
        m_inComment = false;
        return true;
    }

    if (m_inComment)
    {
        return true;
    }

    auto contentTmp = StringHelper(content).removeSpaceAndTab();
    auto ret = contentTmp.find("//");
    if (ret != string::npos
        && ret == 0)
    {
        return true;
    }
    return false;
}

std::string CodeFilter::removeComment(const std::string& content)
{
    size_t targetIndex = string::npos;
    vector<string> keys = { "//", "/*" };
    string targetKey = keys[0];
    for (const auto& element : keys)
    {
        auto index = content.find(element);
        if (index != string::npos)
        {
            if (targetIndex == string::npos
                || targetIndex > index)
            {
                targetIndex = index;
                targetKey = element;
            }
        }
    }

    if (targetIndex != string::npos)
    {
        if (!StringHelper(content).betweenEdge(targetKey, "\""))
        {
            return content.substr(0, targetIndex);
        }
    }

    return content;
}
