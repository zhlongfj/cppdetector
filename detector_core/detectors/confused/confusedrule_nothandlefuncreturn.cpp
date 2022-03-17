#include "confusedrule_nothandlefuncreturn.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"
#include "detectorcommon/functiondefinition.h"

ConfusedRuleNotHandleFuncReturn::ConfusedRuleNotHandleFuncReturn() : Rule("ConfusedRuleNotHandleFuncReturn")
, m_functionDefinition(make_unique<FunctionDefinition>())
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Error, m_name,
        "The function returns a value, but does not process it.",
        U8("函数有返回值，却没有处理"));
}

ConfusedRuleNotHandleFuncReturn::~ConfusedRuleNotHandleFuncReturn() = default;

bool ConfusedRuleNotHandleFuncReturn::detectCore(const string & code, const ErrorFile & errorFile)
{
    if (m_functionDefinition->isFunctionDefinition(code))
    {
        if (m_functionDefinition->getReturnType() != "void")
        {
            m_funcsWithReturn.emplace(m_functionDefinition->getFuncName());
            return false;
        }
    }

    auto ret = DetectorHelper::getInfoOfFunctionCalled(code);
    if (ret.funcName.empty()
        || m_funcsWithReturn.find(ret.funcName) == m_funcsWithReturn.end())
    {
        return false;
    }

    if (!ret.retValue.empty())
    {
        return false;
    }

    storeRuleError(errorFile);
    return true;
}

void ConfusedRuleNotHandleFuncReturn::resetData()
{
    Rule::resetData();
    m_functionDefinition->resetData();
    m_funcsWithReturn.clear();
}
