//
// Created by Hualong Zhang on 2021/4/26.
//
#pragma once
#include "detector_global.h"
#include <string>
#include <utility>
#include <regex>

#define U8(str) u8##str
#define U16(str) L##str
// #ifdef _WIN32
// //#define OUTPUT_TO_TERMINAL
// #ifndef OUTPUT_TO_TERMINAL
// #define U8(str) u8##str
// #endif
// #else
// #define U8(str) str
// #endif

struct FuncInfoOfCalled
{
    std::string funcName;
    std::string retValue;
};

using namespace std;

class DETECTOR_EXPORT DetectorHelper final {
public:
    static smatch check(const string& content, const string& regValue);
    static smatch checkExportClass(const string& content);
    static smatch checkFor(const string& code);
    static std::smatch checkInBracket(const string& code, const string& prefix);
    static smatch checkIf(const string& code);
    static size_t getIndexOfRightBrace(const string& code);
    static smatch checkNew(const string& code);
    static smatch checkConstructedObject(const string& code);
    static smatch checkTernaryOperator(const string& code);
    static string checkClassDefinition(const string& code);
    static string checkDestructor(const string& code);
    static bool isFunctionDefinition(const string& content);
    static string getNameOfFunctionDefinition(const string& content);
    static FuncInfoOfCalled getInfoOfFunctionCalled(const string& content);
    static string getReturnTypeOfFunctionDefinition(const string& content);
    static pair<string, string> getValueFromOperator(const string& content, const string& operationalCharacter);
    static std::smatch checkFor1(const string& code);
};
