//
// Created by Hualong Zhang on 2021/4/27.
//

#include <fstream>
#include <iostream>
#include "filehelp.h"
#include <sstream>
#include <iosfwd>

using namespace std;

bool FileHelp::write(const std::string& filePath, const std::string& content)
{
    ofstream outFile(filePath);
    if (!outFile.is_open())
    {
        return false;
    }
    outFile << content;
    return true;
}

string FileHelp::parse(const std::string& filePath)
{
    m_fileData.clear();
    m_lines.clear();
    ifstream inFile(filePath);
    if (!inFile.is_open())
        return "";
    std::string line;
    while (std::getline(inFile, line))
        m_fileData += line + "\n";

    return m_fileData;
}

std::vector<std::string> FileHelp::getLines()
{
    if (!m_lines.empty())
    {
        return m_lines;
    }

    std::istringstream iStream(m_fileData);
    std::string line;

    while (std::getline(iStream, line)) {
        m_lines.emplace_back(line);
    }
    return m_lines;
}