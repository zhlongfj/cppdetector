#include "memleakrule_filehandle.h"
#include "detectorcommon/detectorhelp.h"

MemLeakRuleFileHandle::MemLeakRuleFileHandle() : Rule("MemLeakRuleFileHandle")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        U8("文件句柄泄漏"));
}

bool MemLeakRuleFileHandle::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (code.find("fopen") == string::npos
        && code.find("fclose") == string::npos)
    {
        return false;
    }

    if (auto ret = DetectorHelper::check(code, "(\\w+)\\s*=\\s*fopen"); !ret.empty())
    {
        //check "FILE* pFile = fopen("c:\\test.txt", "w+");"
        m_resources.insert({ ret[1], errorFile });
        return false;
    }

    if (auto ret = DetectorHelper::check(code, "fclose\\((\\w+)\\)"); !ret.empty())
    {
        auto count = m_resources.count(ret[1]);
        if (count == 1)
        {
            m_resources.erase(m_resources.find(ret[1]));
        }
        return false;
    }

    return false;
}

void MemLeakRuleFileHandle::resetData()
{
    Rule::resetData();
    for_each(m_resources.begin(), m_resources.end(), [this](const auto& item) {return storeRuleError(item.second); });
    m_resources.clear();
}

