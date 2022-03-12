#pragma once
#include <iostream>
#include <string>

class CodeFilter final
{
public:
    std::string filterCode(const std::string& content);
    bool invalidCode(const std::string& content);
    std::string removeComment(const std::string& content);
    void resetData()
    {
        m_inComment = false;
    }

private:
    bool isComment(const std::string& content);
    bool m_inComment = false;
};