#pragma once
#include <string>
#include <utility>
#include "detector_global.h"
using namespace std;

class DETECTOR_EXPORT ArrayRuleHelper final
{
public:
    void makeData(const std::string& filePath);
    int getIndexWithString(const std::string& var, const std::string& filePath);

    pair<int, std::string> getIndex(const std::string& arrayLen, const std::string& filePath);

    std::string getData()
    {
        return m_data;
    }

    void setData(const std::string& data)
    {
        m_data = data;
    }

    void clear()
    {
        m_data.clear();
    }

private:
    std::string m_data;
};
