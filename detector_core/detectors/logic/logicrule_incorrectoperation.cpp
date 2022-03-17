#include "logicrule_incorrectoperation.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"

LogicRuleIncorrectOperation::LogicRuleIncorrectOperation() : Rule("LogicRuleIncorrectOperation")
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Warning, m_name,
        "A logical operation that is always true or false. Or the same judgment condition is written twice.",
        U8("总是为真或为假的逻辑运算，或同一判断条件写两遍"));
}

bool LogicRuleIncorrectOperation::detectCore(const string& code, const ErrorFile& errorFile)
{
    if (auto ret = DetectorHelper::check(code, "if\\s*\\(\\s*(.+)([!=]=)(.+)\\s*\\n*\\s*(\\|\\||&&)\\s*\\n*\\s*(.+)([!=]=)(.+)\\s*\\)"); !ret.empty())
    {
        //check "if ((a != 1) || (a != 3)) {}" or "if ((a == 1) && (a == 3)) {}"
        if (ret[2] == ret[6])
        {
            if (ret[2] == "==" && ret[4] == "&&"
                || ret[2] == "!=" && ret[4] == "||")
            {
                set<string> objects = {
                    DetectorHelper::check(ret[1], R"delimiter((\w+)\s*\)*\s*$)delimiter")[1],
                    DetectorHelper::check(ret[3], R"delimiter((\w+)\s*\)*\s*$)delimiter")[1],
                    DetectorHelper::check(ret[5], R"delimiter((\w+)\s*\)*\s*$)delimiter")[1],
                    DetectorHelper::check(ret[7], R"delimiter((\w+)\s*\)*\s*$)delimiter")[1]
                };

                if (objects.size() == 2)
                {
                    storeRuleError(errorFile);
                    return true;
                }

                if (objects.size() == 3)
                {
                    if (objects.find("string::nnpos") != objects.end()
                        || objects.find("nullptr") != objects.end()
                        || objects.find("NULL") != objects.end()
                        || objects.find("end()") != objects.end())
                    {
                        return false;
                    }

                    auto countOfDigit = count_if(objects.begin(), objects.end(), [](const string& element) {
                        return StringHelper(element).isDigit();
                        });

                    auto countOfString = count_if(objects.begin(), objects.end(), [](const string& element) {
                        return element.find("\"") != string::npos;
                        });

                    if (countOfDigit <= 1
                        && countOfString <= 1)
                    {
                        return false;
                    }

                    storeRuleError(errorFile);
                    return true;
                }
            }
        }
    }
    return false;
}

void LogicRuleIncorrectOperation::resetData()
{
    Rule::resetData();
}

