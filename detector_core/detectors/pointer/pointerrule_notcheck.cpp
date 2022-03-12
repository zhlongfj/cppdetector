#include "pointerrule_notcheck.h"
#include "pointerrule_helper.h"
#include "detectorcommon/detectorhelp.h"

PointerRuleNotCheck::PointerRuleNotCheck() : Rule("PointerRuleNotCheck")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Critical, m_name,
        U8("部分对指针判空，而部分没有判空。"));
}

bool PointerRuleNotCheck::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (auto ret = checkTernaryOperator(code); ret.first)
    {
        if (ret.second)
        {
            storeRuleError(errorFile);
            return true;
        }
        return false;
    }

    if (getPointerFromIf(code))
    {
        return false;
    }

    if (code.find("=") != string::npos)
    {
        if (auto ret = DetectorHelper::check(code, "(\\w+)\\s*=\\s*\\w+"); !ret.empty())
        {
            m_objNames[ret[1]] = { false, false };
        }
    }

    if (auto ret = DetectorHelper::checkConstructedObject(code); !ret.empty())
    {
        auto variable = ret[1].str();
        m_objNames.erase(variable);
    }

    if (code.find("=") != string::npos
        && code.find("==") == string::npos)
    {
        if (auto ret = DetectorHelper::checkConstructedObject(code); !ret.empty())
        {
            auto content = ret[1].str();
            auto iter = find_if(m_objNames.begin(), m_objNames.end(),
                [content](const pair<string, PointerCheck>& item) {return content == item.first; });
            if (iter != m_objNames.end())
            {
                m_objNames.erase(iter->first);
            }
        }
    }

    if (endOfCondition(code))
    {
        return false;
    }


    auto variable = PointerRuleHelper::getDereferenceVariable(code);
    bool inChecked = false;
    for (auto& item : m_objNames)
    {
        if (!item.second.checked || item.second.inChecked)
        {
            if (item.second.inChecked)
            {
                inChecked = true;
            }
            continue;
        }

        if (storeRuleErrorFromNotCheckNames(item))
        {
            return true;
        }
    }

    if (!variable.empty()
        && !inChecked)
    {
        m_notCheckNames.emplace(variable, errorFile);
    }
    return false;
}

pair<bool, bool> PointerRuleNotCheck::checkTernaryOperator(const string& code)
{
    auto ret = DetectorHelper::checkTernaryOperator(code);
    if (ret.empty())
    {
        return { false, false };
    }

    //specs_ ? writer_.write_str(sv, *specs_) : writer_.write(sv);
    //format_specs specs = specs_ ? *specs_ : format_specs();
    //specs_ == nullptr ? writer_.write_str(sv, *specs_) : writer_.write(sv);
    string firstOfTernaryOperator = ret[1];
    if (auto ret1 = DetectorHelper::check(firstOfTernaryOperator, "(\\w+\\s*[!=]=\\s*)?\\w+\\s*$"); !ret1.empty())
    {
        firstOfTernaryOperator = ret1[0];
    }
    auto variableFromTernary = StringHelper(firstOfTernaryOperator).removeSpaceAndTab();
    auto variable = PointerRuleHelper::getDereferenceVariable(code);
    if (variableFromTernary == variable
        || variableFromTernary == "!" + variable)
    {
        return { true, false };
    }

    if (auto ret1 = DetectorHelper::check(firstOfTernaryOperator, "(\\w+)\\s*[!=]=\\s*(\\w+)"); !ret1.empty())
    {
        if (ret1[1] == variable
            || ret1[2] == variable)
        {
            return { true, false };
        }
    }
    return { true, true };;
}
void PointerRuleNotCheck::resetData()
{
    Rule::resetData();
    m_objNames.clear();
    m_notCheckNames.clear();
    m_sapceBeforeIf.clear();
}

bool PointerRuleNotCheck::storeRuleErrorFromNotCheckNames(const std::pair<std::string, PointerCheck>& item)
{
    bool removeVariable = false;
    for (auto& element : m_notCheckNames)
    {
        if (element.first == item.first)
        {
            storeRuleError(element.second);
            removeVariable = true;
        }
    }
    if (removeVariable)
    {
        m_notCheckNames.erase(item.first);
    }
    return removeVariable;
}

bool PointerRuleNotCheck::getPointerFromIf(const string& code)
{
    auto objNames = PointerRuleHelper::getPointerFromIf(code);
    if (objNames.empty())
    {
        return false;
    }

    m_sapceBeforeIf = StringHelper(code).continuousCharactersFromStart(" ");
    for (const auto item : objNames)
    {
        if (!item.empty())
        {
            m_objNames[item] = { true, true };
        }
    }
    return true;
}

bool PointerRuleNotCheck::endOfCondition(const string& code)
{
    string spacesBeforeRightBrace;
    StringHelper helper(code);
    if (helper.findCode("}"))
    {
        auto index = code.find("}");
        auto spaces = helper.continuousCharactersFromStart(" ");
        if (spaces.size() == index)
        {
            spacesBeforeRightBrace = spaces;
        }
    }
    if (!m_sapceBeforeIf.empty() && m_sapceBeforeIf == spacesBeforeRightBrace
        || DetectorHelper::isFunctionDefinition(code))
    {
        m_sapceBeforeIf.clear();
        for (auto& item : m_objNames)
        {
            item.second.inChecked = false;
        }
        return true;
    }

    return false;
}

