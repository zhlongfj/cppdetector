#include "arrayrule_indexoutofboundsinloop.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"
#include "arrayrulehelper.h"
#include "detectorcommon/fordefinition.h"

ArrayRuleIndexOutOfBoundsInLoop::ArrayRuleIndexOutOfBoundsInLoop()
    : ArrayRuleIndexOutOfBoundsInLoop(make_unique<ArrayRuleHelper>())
{

}

ArrayRuleIndexOutOfBoundsInLoop::ArrayRuleIndexOutOfBoundsInLoop(std::unique_ptr<ArrayRuleHelper> helper)
    : Rule("ArrayRuleIndexOutOfBoundsInLoop")
    , m_helper(move(helper))
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Critical, m_name,
        U8("循环语句中下标越界"));
}

ArrayRuleIndexOutOfBoundsInLoop::~ArrayRuleIndexOutOfBoundsInLoop() = default;

bool ArrayRuleIndexOutOfBoundsInLoop::detectCore(const string & code, const ErrorFile & errorFile)
{
    if (code.find("[") != string::npos)
    {
        //Performance optimization, filter mismatches
        if (auto ret = DetectorHelper::check(code, R"delimiter(\w+\s+(\w+)\[(\w+)\])delimiter"); !ret.empty())
        {
            //check "int array_temp[100];"
            m_arrays.insert({ ret[1], m_helper->getIndex(ret[2], errorFile.path) });
            return false;
        }
    }

    if (m_maxLenInLoop.empty())
    {
        ForDefinition forDefinition;
        if (!forDefinition.isFor(code))
        {
            return false;
        }
        //check "for (unsigned int i = 0; i <= INDEX; ++i)"
        if (forDefinition.comparationSymbol() == "<=")
        {
            m_maxLenInLoop = forDefinition.endCondition();
        }
        return false;
    }
    else
    {
        if (code.find("[") == string::npos)
        {
            //Performance optimization, filter mismatches
            return false;
        }
        if (auto ret = DetectorHelper::check(code, R"delimiter((\w+)\[(\w+)\])delimiter"); !ret.empty())
        {
            //check "buf[i] = 'a';"
            auto maxLenInLoop = m_maxLenInLoop;
            m_maxLenInLoop.clear();
            if (any_of(m_arrays.begin(), m_arrays.end(), [maxLenInLoop, &ret](const auto& item) {
                return item.first == ret[1] && item.second.second == maxLenInLoop; }))
            {
                storeRuleError(errorFile);
                return true;
            }
        }
    }

    return false;
}

void ArrayRuleIndexOutOfBoundsInLoop::resetData()
{
    Rule::resetData();
    m_arrays.clear();
    m_helper->clear();
    m_maxLenInLoop.clear();
}
