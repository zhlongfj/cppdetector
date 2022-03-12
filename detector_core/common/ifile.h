//
// Created by Hualong Zhang on 2021/4/27.
//

#pragma once
#include <string>
#include <vector>

class IFile {
public:
    virtual bool write(const std::string& filePath, const std::string& content) = 0;
    virtual std::string parse(const std::string& filePath) = 0;
    virtual std::vector<std::string> getLines() { return m_lines; }
    std::string getData() { return m_fileData; }
    virtual ~IFile() {};
protected:
    std::string m_fileData;
    std::vector<std::string> m_lines;
};