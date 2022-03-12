#include "arrayrule_memsetzerobyte.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"

ArrayRuleMemsetZeroByte::ArrayRuleMemsetZeroByte() : Rule("ArrayRuleMemsetZeroByte")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Error, m_name,
        U8("memset第三个参数是要格式化的字节数，不应该为0"));
}

bool ArrayRuleMemsetZeroByte::detectCore(const string& code, const ErrorFile& errorFile)
{
    //if (auto ret = DetectorHelper::check(code, "memset\s*\\(.+0\\s*\\)"); !ret.empty())
    if (StringHelper(code).findIndexOfCode("memset(") == string::npos
        || code.find("0)") == string::npos)
    {
        return false;
    }
    storeRuleError(errorFile);
    return true;
}

void ArrayRuleMemsetZeroByte::resetData()
{
    Rule::resetData();
}

