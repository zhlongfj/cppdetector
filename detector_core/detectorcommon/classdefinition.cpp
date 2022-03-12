#include "classdefinition.h"
using namespace std;

bool ClassDefinition::inClassDefinition(const string& content)
{
    if (StringHelper(content).removeSpaceAndTab() == "};")
    {
        auto spaceFromStart = StringHelper(content).continuousCharactersFromStart(" ");
        if (!m_classInfos.empty()
            && spaceFromStart + "    " == m_classInfo->spaceBeforeVariable)
        {
            m_classInfos.pop_back();
            m_classInfo = nullptr;
            if (!m_classInfos.empty())
            {
                m_classInfo = m_classInfos.back();
            }
        }
        return m_classInfos.size() >= 1;
    }

    if (auto className = DetectorHelper::checkClassDefinition(content); !className.empty())
    {
        auto spaceBeforeVariable = StringHelper(content).continuousCharactersFromStart(" ") + "    ";
        m_classInfo = make_shared<ClassInfo>(className, spaceBeforeVariable);
        if (content.find("struct") != string::npos)
        {
            m_classInfo->isStruct = true;
            m_classInfo->accessControl = "public:";
        }
        m_classInfos.emplace_back(m_classInfo);
        return m_classInfos.size() > 1;
    }

    bool ret = false;
    if (m_classInfo != nullptr)
    {
        auto contentTmp = StringHelper(content).removeSpaceAndTab();
        bool isMember = !m_classInfo->spaceBeforeVariable.empty() && StringHelper(content).continuousCharactersFromStart(" ") == m_classInfo->spaceBeforeVariable;
        ret = isMember || m_accessControls.find(contentTmp) != m_accessControls.end();
    }
    return ret;
}

bool ClassDefinition::isStruct()
{
    bool ret = false;
    if (m_classInfo != nullptr)
    {
        ret = m_classInfo->isStruct;
    }

    return ret;
}

pair<bool, string> ClassDefinition::isConstructor(const string& content)
{
    return check(content, [](const string& className) {
        return className + "(";
        });
}

pair<bool, string> ClassDefinition::isDestructor(const string& content)
{
    return check(content, [](const string& className) {
        return "~" + className + "(";
        });
}

bool ClassDefinition::isVirtual(const string& content)
{
    if (!DetectorHelper::isFunctionDefinition(content))
    {
        return false;
    }

    return content.find("virtual ") != string::npos || content.find(" override") != string::npos;
}

AccessControl ClassDefinition::getAccessControl(const string& content)
{
    if (m_classInfo == nullptr)
    {
        return AccessControl::PRIVATE;
    }
    auto contentTmp = StringHelper(content).removeSpaceAndTab();
    if (m_accessControls.find(contentTmp) != m_accessControls.end())
    {
        m_classInfo->accessControl = contentTmp;
    }

    auto iter = m_accessControls.find(m_classInfo->accessControl);
    if (iter == m_accessControls.end())
    {
        auto msg = "error: cannot not find access control: " + m_classInfo->accessControl;
        std::cout << msg << std::endl;
        throw msg;
    }
    return iter->second;
}

pair<bool, string> ClassDefinition::check(const string& content, function<string(const string&)> func)
{
    auto contentTmp = StringHelper(content).removeSpaceAndTab();
    for (const auto& element : m_classInfos)
    {
        if (contentTmp.find(func(element->className)) != string::npos)
        {
            return { true, element->className };
        }
    }

    return { false, "" };
}

void ClassDefinition::resetData()
{
    m_classInfos.clear();
    m_classInfo = nullptr;
}

int ClassDefinition::getReferenceCount(const string& content, const string& className)
{
    auto index = content.find("(");
    if (index == string::npos)
    {
        throw "getReferenceCount not find: (";
    }

    index = content.find(className, index);
    if (index == string::npos)
    {
        //normal constructor
        return 0;
    }

    int countOfReference = 0;
    while (content[index] != ')' && content[index] != '\0')
    {
        if (content[index] == '&')
        {
            ++countOfReference;
        }
        ++index;
    }
    return countOfReference;
}

std::pair<bool, std::string> ClassDefinition::isAssignment(const string& content)
{
    return check(content, [](const string& className) {
        return "operator=(const" + className;
        });
}
