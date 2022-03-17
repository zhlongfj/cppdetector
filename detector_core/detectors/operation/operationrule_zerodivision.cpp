#include "operationrule_zerodivision.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"
#include "common/filehelp.h"

OperationRuleZeroDivision::OperationRuleZeroDivision() : Rule("OperationRuleZeroDivision")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Critical, m_name,
        "Divide by zero or modulo zero",
        U8("被零除或对零求模"));
}

bool OperationRuleZeroDivision::detectCore(const string& code, const ErrorFile& errorFile)
{
    auto findDivision = code.find("/") != string::npos;
    auto findModule = code.find("%") != string::npos;
    auto valid = (findDivision || findModule) && code.find("\"") == string::npos;
    if (!valid)
    {
        return false;
    }

    if (auto ret = DetectorHelper::check(code, "\\w+\\s*[%/]\\s*(\\w+)"); !ret.empty())
    {
        auto operatedNum = ret[1].str();
        if (StringHelper(operatedNum).isDigit())
        {
            if (operatedNum == "0")
            {
                storeRuleError(errorFile);
                return true;
            }
        }
        else
        {
            auto data = FileHelp().parse(errorFile.path);
            if (auto ret1 = DetectorHelper::check(data, operatedNum + "\\s*=\\s*(\\w+)"); !ret1.empty())
            {
                if (ret1[1] == "0")
                {
                    storeRuleError(errorFile);
                    return true;
                }
            }
        }
    }

    return false;
}

void OperationRuleZeroDivision::resetData()
{
    Rule::resetData();
}

