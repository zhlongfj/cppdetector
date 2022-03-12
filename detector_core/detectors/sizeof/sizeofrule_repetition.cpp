#include "sizeofrule_repetition.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"

SizeOfRuleRepetition::SizeOfRuleRepetition() : Rule("SizeOfRuleRepetition")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        U8("无意义的重复使用sizeof，可能是失误造成的"));
}

bool SizeOfRuleRepetition::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (!StringHelper(code).findCode("sizeof(sizeof"))
    {
        return false;
    }

    storeRuleError(errorFile);
    return true;
}

void SizeOfRuleRepetition::resetData()
{
    Rule::resetData();
    m_arrayName.clear();
}

