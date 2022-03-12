#include "arrayrule_indexoutofboundsfromfunc.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"
#include "arrayrulehelper.h"

ArrayRuleIndexOutOfBoundsFromFunc::ArrayRuleIndexOutOfBoundsFromFunc()
    : ArrayRuleIndexOutOfBoundsFromFunc(make_unique<ArrayRuleHelper>())
{

}

ArrayRuleIndexOutOfBoundsFromFunc::ArrayRuleIndexOutOfBoundsFromFunc(std::unique_ptr<ArrayRuleHelper> helper)
    : Rule("ArrayRuleIndexOutOfBoundsFromFunc")
    , m_helper(move(helper))
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Critical, m_name,
        U8("函数的返回值最大可能为缓冲区大小，可能造成越界"));
}

ArrayRuleIndexOutOfBoundsFromFunc::~ArrayRuleIndexOutOfBoundsFromFunc() = default;

bool ArrayRuleIndexOutOfBoundsFromFunc::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (code.find("[") != string::npos)
    {
        //Performance optimization, filter mismatches
        if (auto ret = DetectorHelper::check(code, "\\w+\\s+(\\w+)\\[(\\w+)\\]"); !ret.empty())
        {
            //check "int array_temp2[MAX1];"
            m_arrays.insert({ ret[1], m_helper->getIndex(ret[2], errorFile.path) });
            return false;
        }
    }

    if (!m_nameIndexPair.first.empty())
    {
        if (code.find("[") == string::npos)
        {
            //Performance optimization, filter mismatches
            return false;
        }
        if (auto ret = DetectorHelper::check(code, "(\\w+)\\[(\\w+)\\]"); !ret.empty())
        {
            //check "buf[length] = 'Q';"
            if (m_nameIndexPair.first == ret[1]
                && m_nameIndexPair.second == ret[2])
            {
                storeRuleError(errorFile);
                m_nameIndexPair = { "", "" };
                return true;
            }
        }
        return false;
    }

    if (code.find("(") == string::npos)
    {
        //Performance optimization, filter mismatches
        return false;
    }
    if (auto ret = DetectorHelper::check(code, "\\w+\\s+(\\w+)\\s*=\\s*\\w+\\("); !ret.empty())
    {
        //check "int length = getLenFromBuf(INDEX1);"
        for (const auto& item : m_arrays)
        {
            if (code.find(item.second.second) != string::npos)
            {
                m_nameIndexPair = { item.first, ret[1] };
                return false;
            }
        }
    }

    return false;
}

void ArrayRuleIndexOutOfBoundsFromFunc::resetData()
{
    Rule::resetData();
    m_arrays.clear();
    m_helper->clear();
    m_nameIndexPair = { "", "" };
}


