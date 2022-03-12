#include "iteratorrule_invaliddereference.h"
#include "../../common/stringhelper.h"
#include "detectorcommon/detectorhelp.h"

IteratorRuleInvalidDereference::IteratorRuleInvalidDereference() : Rule("IteratorRuleInvalidDereference")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Critical, m_name,
        U8("解引用end()迭代器"));
}

bool IteratorRuleInvalidDereference::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (code.find("if") != string::npos
        && code.find("end()") != string::npos)
    {
        if (auto ret = DetectorHelper::check(code, "if\\s*\\(\\s*(.+)\\s*==\\s*(.+)\\)"); !ret.empty())
        {
            //check "    if (iter == ivec.end())"
            auto sizeName = "end()";
            if (ret[1].str().find(sizeName) != string::npos)
            {
                m_iteratorName = StringHelper(ret[2]).removeSpaceAndTab();
            }

            if (ret[2].str().find(sizeName) != string::npos)
            {
                m_iteratorName = StringHelper(ret[1]).removeSpaceAndTab();
            }

            if (m_iteratorName.empty())
            {
                return false;
            }

            auto prefix = code.substr(0, code.find(ret[0]));
            m_spaces = prefix + "    ";
            return false;
        }
    }

    if (m_spaces.empty())
    {
        return false;
    }

    auto index = code.find("}");
    if (StringHelper(code).findCode("else")
        || index != string::npos && index == m_spaces.size() - 4)
    {
        resetData();
        return false;
    }

    return checkReference(code, errorFile);
}

void IteratorRuleInvalidDereference::resetData()
{
    Rule::resetData();
    m_iteratorName.clear();
    m_spaces.clear();
}

bool IteratorRuleInvalidDereference::checkReference(const string& code, const ErrorFile& errorFile)
{
    auto index = code.find(m_iteratorName);
    if (index == string::npos)
    {
        return false;
    }
    //check "iter->value_type, *iter, ivec.find(3)->value_type or *(ivec.find(3))"
    auto index1 = code.find("*");
    auto index2 = code.find("->", index + m_iteratorName.size());
    if (index2 == string::npos
        && (index1 == string::npos || index1 >= index))
    {
        return false;
    }

    auto prefix = DetectorHelper::check(code, "\\s*")[0].str();
    if (m_spaces.size() != prefix.size())
    {
        return false;
    }

    storeRuleError(errorFile);
    return true;
}

