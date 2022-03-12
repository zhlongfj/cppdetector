#pragma once
#include <string>
#include <vector>
#include <functional>
using namespace std;

template<class T>
class MapHelp final {
public:
    explicit MapHelp(const map<string, T>& elements) : m_elements(elements) {}
    map<string, T> erase(const T& reference, function<bool(const T& element, const T& reference)> func)
    {
        for (auto iter = m_elements.begin(); iter != m_elements.end();)
        {
            if (func(iter->second, reference))
            {
                m_elements.erase(iter++);
            }
            else
            {
                ++iter;
            }
        }
        return m_elements;
    }
private:
    map<string, T> m_elements;
};
