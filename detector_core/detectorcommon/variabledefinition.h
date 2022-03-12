#pragma once

#include <string>
#include <stack>
#include "../common/stringhelper.h"
#include "detectorhelp.h"

using namespace std;

class DETECTOR_EXPORT VariableDefinition final {
public:
    bool isVariableDefinition(const string& content);

    bool checkPoint(const string& content, const string& pointMark);

    bool isStatic() { return m_isStatic; }

    bool isConstexpr() { return m_isConstexpr; }

    bool isPoint() { return m_isPoint; }

    bool isPointToPoint() { return m_isPointToPoint; }

    bool isInitialized() { return m_isInitialized; }

    string type() { return m_type; }
    
    std::string name() { return m_name; }

private:

    string separateOutVariableDeclaration(const string& code);
    bool validType(const string& code);
    void resetData();

    string m_content;
    bool m_isStatic = false;
    bool m_isConst = false;
    bool m_isConstexpr = false;
    bool m_isPoint = false;
    bool m_isPointToPoint = false;
    bool m_isReference = false;
    bool m_isRvalueReference = false;
    bool m_isInitialized = false;
    string m_type;
    string m_name;
};