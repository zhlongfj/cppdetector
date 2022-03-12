#pragma once
#include <string>
#include "common/stringhelper.h"
#include "detectorhelp.h"
using namespace std;

class DETECTOR_EXPORT BraceHelper final
{
public:
    int calculateCountOfOpenBrace(const string& code);
    bool findOpenBrace() { return m_findOpenBrace; }
    void resetData();

private:
    void reduceCountOfOpenBrace();
    bool openBraceAtBegin(const string& codeWithoutSpace);
    bool openBraceAfterCloseParenthesis(const string& codeWithoutSpace);
    bool closeBrace(const string& codeWithoutSpace);
    int m_countOfOpenBrace = 0;
    bool m_findOpenBrace = false;
};