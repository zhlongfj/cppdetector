#pragma once
#include <string>
#include <stack>
#include "../common/stringhelper.h"
#include "detectorhelp.h"

using namespace std;

struct DETECTOR_EXPORT ConditionContext final
{
    std::string conditionExpresss;
    std::string operatorName;
    std::pair<std::string, std::string> operands;
    std::string logicalOperatorToNext;
};

class DETECTOR_EXPORT IfDefinition final
{
public:
    bool inIfDefinition(const std::string& content);
    void resetData();
    bool isEnd() { return m_isEnd; }
    std::string condition() { return m_condition; }
    const std::vector<ConditionContext>& getConditionContexts() { return m_conditionContexts; }

private:
    std::size_t findEnd(const string& content);
    void addCondition(const string& content);
    void handleCondition(const string& content, const size_t& indexOfStart);

    void generateIfConfition(std::string& condition, const std::pair<std::string, std::size_t>& localOperator);

    std::pair<std::string, std::size_t> getLocalOperator(std::string& condition);

    std::string m_condition;
    std::vector<ConditionContext> m_conditionContexts;
    bool m_isEnd = false;
    bool m_inDefinition = false;
};