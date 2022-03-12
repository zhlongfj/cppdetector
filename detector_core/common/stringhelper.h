#pragma once
#include <string>
#include <vector>
#include "detector_global.h"
using namespace std;
class DETECTOR_EXPORT StringHelper final
{
public:
    explicit StringHelper(const string& content) : m_content(content) {}
    vector<string> getLines();
    vector<string> split(const string& delims);
    bool isDigit();
    string replace(const string& source, const string& target);
    string removeSpaceAndTab();
    string removeBeginSpaceAndTab();
    string removeEndSpaceAndTab();
    string trim();
    string toLower();
    size_t count(const char& target);
    string continuousCharactersFromStart(const string& characters);
    string removeFromStart(const string& characters);
    bool remove(const string& target);
    bool findCode(const string& target);
    std::size_t findIndexOfCode(const string& target);
    bool isNull();
    bool isReturnNull();
    bool betweenEdge(const string& target, const string& edge);
    size_t getIndexAfterTarget(const string& target);
    string getVariableFromSelfOperation(const string& selfOperation);
    string content() const { return m_content; }

private:
    string m_content;
};
