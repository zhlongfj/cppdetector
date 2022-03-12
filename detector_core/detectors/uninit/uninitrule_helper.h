#pragma once
#include "detectorcommon/detectorhelp.h"
#include "detectorcommon/detectorcommon.h"
#include <string>
#include <set>
#include <map>

class UninitRuleVariableDefinitionHelper final {
public:
    bool detectCore(const ErrorFile& errorFile, const std::string& variableName);

    std::vector<ErrorFile> resetData();

    void checkClass(const std::string& code);

private:
    void resetEndOfClass();

    std::string m_className;
    bool m_findConstructor = false;
    bool m_inConstructor = false;
    int m_countOfLeftBrace = 0;
    std::map<std::string, std::set<std::string>> m_initializedVariables;
    std::multimap<std::string, pair<std::string, ErrorFile>> m_definedVariables;
};
