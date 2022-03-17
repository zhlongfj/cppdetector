#include "memleakrule_newwithoutdelete.h"
#include "detectorcommon/detectorhelp.h"

MemLeakRuleNewWithOutDelete::MemLeakRuleNewWithOutDelete() : Rule("MemLeakRuleNewWithOutDelete")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        "new an object. Forget to delete or use free to release memory.",
        U8("new了一个对象，忘记delete或采用free来释放内存"));
}

bool MemLeakRuleNewWithOutDelete::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (code.find("new ") == string::npos
        && code.find("delete ") == string::npos)
    {
        return false;
    }

    if (auto ret = DetectorHelper::checkNew(code); !ret.empty())
    {
        //check "m_tt = new Test();"
        m_objectCreateByNew.insert({ ret[1], errorFile });
        return false;
    }

    if (auto ret = DetectorHelper::check(code, "delete\\s+(\\[\\])*(\\w+)"); !ret.empty())
    {
        auto iter = m_objectCreateByNew.find(ret[2]);
        if (iter != m_objectCreateByNew.end())
        {
            m_objectCreateByNew.erase(iter);
        }
        return false;
    }

    return false;
}

void MemLeakRuleNewWithOutDelete::resetData()
{
    Rule::resetData();
    for_each(m_objectCreateByNew.begin(), m_objectCreateByNew.end(), [this](const auto& item) {return storeRuleError(item.second); });
    m_objectCreateByNew.clear();
}

