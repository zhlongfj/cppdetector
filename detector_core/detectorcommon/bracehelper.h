#pragma once
#include <string>
#include "common/stringhelper.h"
#include "detectorhelp.h"
using namespace std;

class DETECTOR_EXPORT BraceHelper final
{
public:
    int calculateCountOfOpenBrace(const string& code, const int line);
    bool findOpenBrace() { return m_findOpenBrace; }
    void resetData();

private:
    void reduceCountOfOpenBrace(const int line);
    bool openBraceAtBegin(const string& codeWithoutSpace);
    bool openBraceAfterCloseParenthesis(const string& codeWithoutSpace);
    bool closeBrace(const string& codeWithoutSpace);
    int m_countOfOpenBrace = 0;
    bool m_findOpenBrace = false;
};