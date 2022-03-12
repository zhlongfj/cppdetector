//
// Created by Hualong Zhang on 2021/4/27.
//
#pragma once
#include <string>
#include <vector>

using namespace std;

class IPath {
public:
    std::vector<std::string> getFilePaths() { return m_filePaths; }
    virtual ~IPath() {}
protected:
    std::vector<std::string> m_filePaths;
};
