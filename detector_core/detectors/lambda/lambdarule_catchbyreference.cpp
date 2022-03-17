#include "lambdarule_catchbyreference.h"
#include "detectorcommon/detectorhelp.h"

LambdaRuleCatchByReference::LambdaRuleCatchByReference() : Rule("LambdaRuleCatchByReference")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        "Lambda expressions should not capture all variables by reference.",
        U8("Lambda expressions cannot capture all variables by reference."));
}

bool LambdaRuleCatchByReference::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (code.find("[") == string::npos
        || code.find("&") == string::npos)
    {
        return false;
    }

    auto ret = DetectorHelper::check(code, "\\[.*&(.*)\\]\\(");
    if (ret.empty())
    {
        return false;
    }

    auto capturedVar = ret[1].str();
    if (!capturedVar.empty()
        && !DetectorHelper::check(ret[1], "^\\s*(_\\w)*").empty())
    {
        return false;
    }
    //check "void fontManger(startTransferProgram, [&](const int errorCode, const std::string& result) {"
    storeRuleError(errorFile);
    return true;
}

