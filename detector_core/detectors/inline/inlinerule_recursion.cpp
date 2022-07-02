#include "inlinerule_recursion.h"
#include "detectorcommon/bracehelper.h"
#include "detectorcommon/detectorhelp.h"
using namespace std;

InlineRuleRecursion::InlineRuleRecursion() : Rule("InlineRuleRecursion")
    , braceHelper(make_unique<BraceHelper>())
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Suggest, m_name,
        "Do not define a recursive function as an inline function.",
        U8("请不要将递归函数定义成内联函数"));
}

InlineRuleRecursion::~InlineRuleRecursion() = default;

bool InlineRuleRecursion::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (errorFile.path.find(".h") == string::npos)
    {
        return false;
    }

    auto nameOfFunc = DetectorHelper::getNameOfFunctionDefinition(code);
    if (!nameOfFunc.empty())
    {
        resetData();
        m_nameOfFunctionDefinition = nameOfFunc;
        m_lineOfFunction = errorFile.line;
        auto target = "inline ";
        if (code.find(target) != string::npos
            && !StringHelper(code).betweenEdge(target, "\""))
        {
            m_isInline = true;
        }
    }

    if (m_lineOfFunction == 0
        || !m_isInline)
    {
        return false;
    }

    int countOfLeftBrace = braceHelper->calculateCountOfOpenBrace(code, errorFile.line);
    if (!braceHelper->findOpenBrace())
    {
        return false;
    }
    else
    {
        auto nameOfFuncCalled = DetectorHelper::getInfoOfFunctionCalled(code);
        if (nameOfFuncCalled.funcName == m_nameOfFunctionDefinition)
        {
            storeRuleError({ m_lineOfFunction, errorFile.path });
            resetData();
            return true;
        }
    }

    return false;
}

void InlineRuleRecursion::resetData()
{
    m_isInline = false;
    m_lineOfFunction = 0;
    m_nameOfFunctionDefinition.clear();
    braceHelper->resetData();
    Rule::resetData();
}

