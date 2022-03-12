#include "inlinerule_complexfunction.h"
#include "detectorcommon/bracehelper.h"
#include "detectorcommon/detectorhelp.h"

InlineRuleComplexFunction::InlineRuleComplexFunction() : Rule("InlineRuleComplexFunction")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Suggest, m_name,
        U8("不要内联包含循环或 switch 语句的函数"));
}

bool InlineRuleComplexFunction::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (errorFile.path.find(".h") == string::npos)
    {
        return false;
    }

    if (DetectorHelper::isFunctionDefinition(code))
    {
        resetData();
        if (code.find("}") == code.size() - 1)
        {
            //The function definition and content are on the same line
            return false;
        }

        m_lineOfFunction = errorFile.line;
        m_spacesBeforeFunction = StringHelper(code).continuousCharactersFromStart(" ");
        auto target = "inline ";
        if (code.find(target) != string::npos
            && !StringHelper(code).betweenEdge(target, "\""))
        {
            m_isInline = true;
        }
    }

    if (m_lineOfFunction == 0)
    {
        return false;
    }

    if (code.find("}") == code.size() - 1)
    {
        if (m_spacesBeforeFunction == StringHelper(code).continuousCharactersFromStart(" "))
        {
            resetData();
            return false;
        }
    }

    auto codeTmp = StringHelper(code).removeSpaceAndTab();
    vector<string> statements = { "switch(", "for(", "while(" };
    for (const auto& element : statements)
    {
        auto index = codeTmp.find(element);
        if (index != string::npos
            && !StringHelper(codeTmp).betweenEdge(element, "\""))
        {
            if (m_isInline)
            {
                storeRuleError({ m_lineOfFunction, errorFile.path });
                return true;
            }
        }
    }
    return false;
}

void InlineRuleComplexFunction::resetData()
{
    m_isInline = false;
    m_lineOfFunction = 0;
    Rule::resetData();
}

