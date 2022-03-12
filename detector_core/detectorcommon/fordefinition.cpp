#include "fordefinition.h"
#include "detectorhelp.h"
#include "common/stringhelper.h"

bool ForDefinition::isFor(const std::string& content)
{
    auto ret = DetectorHelper::checkFor1(content);
    if (ret.empty())
    {
        return false;
    }

    //check "for (unsigned int ii = 0; ii <= foo.size(); ++ii)" or "for (unsigned int ii = 0; ii <= ss; ++ii)"

    m_comparationVariable = ret[2];
    m_comparationSymbol = ret[3];
    m_endCondition = ret[4];

    auto variable = StringHelper(ret[1].str()).trim();
    if (auto ret1 = DetectorHelper::check(variable, R"delimiter((\s+)*(\w+)$)delimiter"); !ret1.empty())
    {
        m_type = ret1.prefix().str();
        m_initVariable = ret1[2];
    }

    auto step = ret[5].str();
    if (auto variable = StringHelper(step).getVariableFromSelfOperation("++"); !variable.empty())
    {
        m_stepVariable = variable;
        m_stepOperation = "++";
    }

    if (auto variable = StringHelper(step).getVariableFromSelfOperation("--"); !variable.empty())
    {
        m_stepVariable = variable;
        m_stepOperation = "--";
    }
    return true;
}

void ForDefinition::resetData()
{
    m_type.clear();
    m_initVariable.clear();
    m_comparationVariable.clear();
    m_comparationSymbol.clear();
    m_endCondition.clear();
    m_stepVariable.clear();
    m_stepOperation.clear();
}
