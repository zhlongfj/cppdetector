#include "arrayrule_bufferoverflow.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"
#include "arrayrulehelper.h"

ArrayRuleBufferOverflow::ArrayRuleBufferOverflow()
    :ArrayRuleBufferOverflow(make_unique<ArrayRuleHelper>())
{

}

ArrayRuleBufferOverflow::ArrayRuleBufferOverflow(std::unique_ptr<ArrayRuleHelper> helper) : Rule("ArrayRuleBufferOverflow")
, m_helper(move(helper))
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Critical, m_name,
        "Buffer is accessed out of bounds. The length of the buffer to read and write has exceeded the size of the buffer.",
        U8("访问缓冲区越界，读写缓冲区的长度超过了缓冲区本身的大小"));
}

ArrayRuleBufferOverflow::~ArrayRuleBufferOverflow() = default;

bool ArrayRuleBufferOverflow::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (code.find("[") == string::npos
        && code.find("strcpy") == string::npos
        && code.find("strcat") == string::npos
        && code.find("strncpy") == string::npos
        && code.find("snprintf") == string::npos)
    {
        return false;
    }
    if (auto ret = DetectorHelper::check(code, "\\w+\\s+(\\w+)\\[(\\w+)\\]"); !ret.empty())
    {
        //check "int SizeOfRuleFuncParameterDemo1(int32_t sz[3])" or "int array_temp[100];"
        m_arrays.insert({ ret[1], m_helper->getIndex(ret[2], errorFile.path) });
        return false;
    }

    if (auto ret = DetectorHelper::check(code, "(strcat|strcpy)\\((\\w+),\\s*(.+)\\s*\\)"); !ret.empty())
    {
        //check "strcpy(sz, "123");"
        if (auto iter = m_arrays.find(ret[2]); iter != m_arrays.end())
        {
            int len = 0;
            auto source = ret[3].str();
            if (source.find("\"") != string::npos)
            {
                len = source.size();
            }
            else
            {
                len = m_helper->getIndexWithString(source, errorFile.path);
            }
            if (len >= iter->second.first)
            {
                storeRuleError(errorFile);
                return true;
            }
        }
    }

    if (auto ret = DetectorHelper::check(code, "strncpy\\s*\\((\\w+),\\s*\"*(\\w+)\"*,\\s*(\\w+)\\)"); !ret.empty())
    {
        //check "strncpy(sz, "123", 3);"
        if (auto iter = m_arrays.find(ret[1]); iter != m_arrays.end())
        {
            auto len = m_helper->getIndex(ret[3], errorFile.path).first;
            if (len >= iter->second.first)
            {
                storeRuleError(errorFile);
                return true;
            }
        }
    }

    if (auto ret = DetectorHelper::check(code, "snprintf\\s*\\((\\w+),\\s*(\\w+)"); !ret.empty())
    {
        //check "snprintf(szStrTime, 5, "%s", szBuff);"
        if (auto iter = m_arrays.find(ret[1]); iter != m_arrays.end())
        {
            auto len = m_helper->getIndex(ret[2], errorFile.path).first;
            if (len >= iter->second.first)
            {
                storeRuleError(errorFile);
                return true;
            }
        }
    }

    return false;
}

void ArrayRuleBufferOverflow::resetData()
{
    Rule::resetData();
    m_arrays.clear();
    m_helper->clear();
}
