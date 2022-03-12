#include "uninitrule_helper.h"

bool UninitRuleVariableDefinitionHelper::detectCore(const ErrorFile& errorFile, const string& variableName)
{
    //check "int32_t s;"
    //storeRuleError(errorFile);
    if (m_className.empty())
    {
        return true;
    }
    m_definedVariables.insert({ m_className, { variableName, errorFile } });
    return false;
}

std::vector<ErrorFile> UninitRuleVariableDefinitionHelper::resetData()
{
    vector<ErrorFile> errorFiles;
    for (const auto& item : m_definedVariables)
    {
        if (auto ret = m_initializedVariables.find(item.first); ret != m_initializedVariables.end())
        {
            if (ret->second.find(item.second.first) == ret->second.end())
            {
                errorFiles.push_back(item.second.second);
            }
        }
    }
    resetEndOfClass();
    m_initializedVariables.clear();
    m_definedVariables.clear();
    return errorFiles;
}

void UninitRuleVariableDefinitionHelper::checkClass(const string& code)
{
    if (code == "};")
    {
        resetEndOfClass();
    }
    auto codeTmp = code;
    if (auto className = DetectorHelper::checkClassDefinition(codeTmp); !className.empty())
    {
        m_className = className;
        m_initializedVariables.insert({ className, set<string>() });
    }

    if (m_initializedVariables.empty())
    {
        return;
    }

    for (const auto& item : m_initializedVariables)
    {
        if (codeTmp.find(item.first) == string::npos
            || codeTmp.find("~") != string::npos)
        {
            //can not find class or find destructor
            continue;
        }

        if (codeTmp.find("= default") != string::npos
            || codeTmp.find("= delete") != string::npos)
        {
            continue;
        }

        auto className = item.first;
        if (auto ret = DetectorHelper::check(codeTmp, className + "\\(.*\\)"); !ret.empty())
        {
            //constructor method
            m_findConstructor = true;
            codeTmp = ret[0].str();
            m_className = className;
            break;
        }
    }

    if (!m_findConstructor
        && !m_inConstructor)
    {
        return;
    }

    if (codeTmp.find("{") != string::npos)
    {
        ++m_countOfLeftBrace;
        m_inConstructor = true;
        m_findConstructor = false;
    }

    if (codeTmp.find("}") != string::npos)
    {
        --m_countOfLeftBrace;
    }

    if (m_countOfLeftBrace <= 0)
    {
        auto tmp = codeTmp;
        while (true)
        {
            auto ret = DetectorHelper::check(tmp, "\\s*(\\w+)\\s*[\\(\\{]\\w+[\\)\\}]");
            if (ret.empty())
            {
                break;
            }
            m_initializedVariables[m_className].insert(ret[1].str());
            tmp = tmp.substr(ret[0].length());
        }

        if (m_inConstructor)
        {
            m_inConstructor = false;
        }
    }

    if (m_inConstructor && m_countOfLeftBrace > 0)
    {
        if (auto ret = DetectorHelper::check(codeTmp, "(\\w+)\\s*[\\(\\{=]"); !ret.empty())
        {
            m_initializedVariables[m_className].insert(ret[1].str());
        }
    }
}

void UninitRuleVariableDefinitionHelper::resetEndOfClass()
{
    m_className.clear();
    m_findConstructor = false;
    m_inConstructor = false;
    m_countOfLeftBrace = 0;
}

