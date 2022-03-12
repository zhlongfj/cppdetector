#include "dynamicrulehelper.h"
#include "detectorcommon/detectorhelp.h"

std::pair<std::string, std::string> DynamicRuleHelper::findExportedClass(const std::string& code)
{
    auto ret = DetectorHelper::checkExportClass(code);
    if (ret.empty())
    {
        return { "", "" };
    }

    string subClass = ret[2];
    if (subClass == "final")
    {
        return { "", "" };
    }
    string baseClass = ret[ret.size() - 1];
    return { subClass, baseClass };
}

bool DynamicRuleHelper::findClassDomain(const std::string& code, const string& className)
{
    return code.find(className + "::") != string::npos;
}

