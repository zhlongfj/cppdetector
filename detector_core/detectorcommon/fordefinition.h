//
// Created by Hualong Zhang on 2021/4/26.
//
#pragma once
#include <string>
#include "detector_global.h"

using namespace std;

class DETECTOR_EXPORT ForDefinition final {
public:
    ForDefinition() = default;
    bool isFor(const std::string& content);
    std::string type() { return m_type; }
    std::string initVariable() { return m_initVariable; }
    std::string comparationVariable() { return m_comparationVariable; }
    std::string comparationSymbol() { return m_comparationSymbol; }
    std::string endCondition() { return m_endCondition; }
    std::string stepVariable() { return m_stepVariable; }
    std::string stepOperation() { return m_stepOperation; }
    void resetData();
private:
    //    for (unsigned int i = 0; j <= foo.size(); ++k)
    std::string m_type;                   // unsigned int
    std::string m_initVariable;           // i
    std::string m_comparationVariable;    // j
    std::string m_comparationSymbol;      // <=
    std::string m_endCondition;           // foo.size()
    std::string m_stepVariable;           // k
    std::string m_stepOperation;          // ++

};
