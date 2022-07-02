#include "inlinerule_tenlines.h"
#include "detectorcommon/bracehelper.h"
#include "detectorcommon/detectorhelp.h"
using namespace std;

InlineRuleTenLines::InlineRuleTenLines() : Rule("InlineRuleTenLines")
, braceHelper(make_unique<BraceHelper>())
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Suggest, m_name,
        "Do not define a function with more than 10 lines as an inline function.",
        U8("将不要将10行以上的函数定义成内联函数"));
}

InlineRuleTenLines::~InlineRuleTenLines() = default;

bool InlineRuleTenLines::detectCore(const string & code, const ErrorFile & errorFile)
{
    if (errorFile.path.find(".h") == string::npos)
    {
        return false;
    }

    if (DetectorHelper::isFunctionDefinition(code))
    {
        resetData();
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

    if (countOfLeftBrace == 0)
    {
        bool valid = m_isInline && errorFile.line - m_lineOfFunction >= 10;
        resetData();
        if (valid)
        {
            storeRuleError({ m_lineOfFunction, errorFile.path });
            return true;
        }
    }

    return false;
}

void InlineRuleTenLines::resetData()
{
    m_isInline = false;
    m_lineOfFunction = 0;
    braceHelper->resetData();
    Rule::resetData();
}

