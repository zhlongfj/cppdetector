#pragma once
#include <string>
#include <stack>
#include "../common/stringhelper.h"
#include "detectorhelp.h"

using namespace std;

class DETECTOR_EXPORT FunctionDefinition final
{
public:
    bool inFunctionDefinition(const string& content);

    std::string getFuncName() { return m_funcName; }

    std::string getReturnType() { return m_returnType; }

    bool isFunctionDefinition(const string& content);

    void resetData();
private:
    vector<string> m_sapceBeforeFunctions;
    string m_sapceBeforeFunction;
    string m_funcName;
    string m_returnType;
    bool m_inFunction = false;

};