#pragma once
#include "detectorcommon/detectorhelp.h"

class PointerRuleHelper final {
public:
    static std::string getObjNameOfNull(const std::string& content);

    static std::string getObjNameOfUninitialized(const std::string& content);

    static std::string getDereferenceVariable(const string& content);

    static std::pair<std::string, std::string> getObjNamePairFromIfNotEqual(const std::string& content);

    static std::string getObjNameFromIfNotEqual(const std::string& content);

    static std::string getObjNameFromIfEqual(const std::string& content);

    static std::pair<std::string, std::string> getObjNamePairFromIfEqual(const std::string& content);

    static bool isNull(const std::string& content);

    static bool existNull(const std::string& content);

    static bool detectDereference(const std::string& content, const std::string& objName, std::vector<bool>& inConditions);

    static std::string getObjNameFromPair(const std::pair<std::string, std::string>& names);

    static std::vector<std::string> getPointerFromIf(const std::string& content);

    static std::string getPointerFromCondition(const std::string& condition);

private:
    static std::pair<std::string, std::string> getObjNamePairFromIf(const std::string& content, const std::string& comparisonOperator);
};
