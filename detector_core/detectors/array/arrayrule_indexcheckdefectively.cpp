#include "arrayrule_indexcheckdefectively.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"
#include "../../common/filehelp.h"
#include "arrayrulehelper.h"
#include "detectorcommon/ifdefinition.h"

ArrayRuleIndexCheckDefectively::ArrayRuleIndexCheckDefectively()
    : ArrayRuleIndexCheckDefectively(make_unique<ArrayRuleHelper>())
{

}

ArrayRuleIndexCheckDefectively::ArrayRuleIndexCheckDefectively(std::unique_ptr<ArrayRuleHelper> helper)
    : Rule("ArrayRuleIndexCheckDefectively")
    , m_helper(move(helper))
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Critical, m_name,
        U8("对数组下标的保护存在缺陷，通常是漏掉了数组长度的边界值"));
}

ArrayRuleIndexCheckDefectively::~ArrayRuleIndexCheckDefectively() = default;

bool ArrayRuleIndexCheckDefectively::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (!m_findCheck)
    {
        return false;
    }

    if (code.find("[") != string::npos)
    {
        //Performance optimization, filter mismatches
        if (auto ret = DetectorHelper::check(code, "\\w+\\s+(\\w+)\\[(\\w+)\\]"); !ret.empty())
        {
            //check "int buf[10];"
            m_arrays.insert({ ret[1], m_helper->getIndex(ret[2], errorFile.path) });
            return false;
        }
    }

    if (m_arrays.empty())
    {
        return false;
    }

    if (m_indexAndLen.empty())
    {
        if (m_dataRest.empty())
        {
            m_dataRest = m_helper->getData();
        }

        if (auto ret = DetectorHelper::check(m_dataRest, "\\s*if\\s*\\((\\w+)\\s*[<>]\\s*(\\w+)(\\s*\\n*\\|\\|\\s*(\\w+)\\s*[<>]\\s*(\\w+))*\\)"); ret.empty())
        {
            //check "if (index < 0 || index > 10)"
            m_findCheck = false;
            return false;
        }
        else
        {
            m_checkStatement = StringHelper(ret[0]).replace("\t", "    ");
            if (ret[4].matched && ret[5].matched)
            {
                m_indexAndLen = { ret[1], ret[2],ret[4],ret[5] };
            }
            else
            {
                m_indexAndLen = { ret[1], ret[2] };
            }

            m_dataRest = m_dataRest.substr(m_dataRest.find(ret[0]) + ret[0].length());
        }
    }

    if (!m_indexAndLen.empty())
    {
        if (code.find("if") != string::npos
            && m_checkStatement.find(code) != string::npos)
        {
            auto indexAndLens = m_indexAndLen;
            m_indexAndLen.clear();
            if (any_of(m_arrays.begin(), m_arrays.end(), [&indexAndLens](const auto& item) {
                return any_of(indexAndLens.begin(), indexAndLens.end(), [&item](const auto& item1) {return item.second.second == item1; }); }))
            {
                storeRuleError(errorFile);
                return true;
            }
        }
        return false;
    }

    return false;
}

void ArrayRuleIndexCheckDefectively::resetData()
{
    Rule::resetData();
    m_arrays.clear();
    m_helper->clear();
    m_dataRest.clear();
    m_checkStatement.clear();
    m_indexAndLen.clear();
    m_findCheck = true;
}

