#include "arrayrule_indexusedbeforecheck.h"
#include "detectorcommon/detectorhelp.h"
#include <cctype>
#include "../../common/stringhelper.h"
#include "common/filehelp.h"
#include "arrayrulehelper.h"

ArrayRuleIndexUsedBeforeCheck::ArrayRuleIndexUsedBeforeCheck()
    : ArrayRuleIndexUsedBeforeCheck(std::make_unique<ArrayRuleHelper>())
{

}

ArrayRuleIndexUsedBeforeCheck::ArrayRuleIndexUsedBeforeCheck(std::unique_ptr<ArrayRuleHelper> helper)
    : Rule("ArrayRuleIndexUsedBeforeCheck")
    , m_helper(move(helper))
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Error, m_name,
        U8("先使用下标再检查下表是否越界"));
}

ArrayRuleIndexUsedBeforeCheck::~ArrayRuleIndexUsedBeforeCheck() = default;

bool ArrayRuleIndexUsedBeforeCheck::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (!m_needCheck)
    {
        return false;
    }

    if (m_data.empty())
    {
        m_helper->makeData(errorFile.path);
        m_data = m_helper->getData();
    }

    if (m_target.empty())
    {
        //check "if (buf[index] > 0 && index <= INDEX"
        auto ret = DetectorHelper::check(m_data, "(if\\s*\\(\\s*\\w+\\[\\w+\\]).*\\n*\\s*&&\\n*\\s*(\\w+)\\s*[<=>]+\\s*(\\w+)");
        if (ret.empty())
        {
            m_needCheck = false;
            return false;
        }
        m_target = ret[1];
    }

    if (code.find(m_target) == string::npos)
    {
        return false;
    }

    storeRuleError(errorFile);
    m_data = m_data.substr(m_data.find(code) + code.size());
    return true;
}

void ArrayRuleIndexUsedBeforeCheck::resetData()
{
    Rule::resetData();
    m_data.clear();
    m_target.clear();
    m_needCheck = true;
}
