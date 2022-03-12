//
// Created by Hualong Zhang on 2021/4/27.
//

#include <filesystem>
#include <regex>
#include "cpppath.h"
#include "common/filepath.h"
#include <map>

using namespace std;

CPPPath::CPPPath(const std::string& path) {
    FilePath filePath(path, [](std::filesystem::directory_entry item) {
        if (item.status().type() != filesystem::file_type::regular) {
            return false;
        }
        
        return isCPPCodeFile(item.path().generic_string());
        });
    m_filePaths = filePath.getFilePaths();
    map<string, string> filePaths;
    for (const auto& item : m_filePaths)
    {
        filesystem::path pathIner(item);
        filePaths.insert({ pathIner.filename().string(), item });
    }

    m_filePaths.clear();
    for (auto iter = filePaths.rbegin(); iter != filePaths.rend(); iter++)
    {
        m_filePaths.push_back(iter->second);
    }
    //sort(m_filePaths.rbegin(), m_filePaths.rend());
}

bool CPPPath::isCPPCodeFile(const std::string& filePath)
{
    const auto& genericPath = filesystem::path(filePath).generic_string();
    auto regValue = R"delimiter((\.h|\.cpp|\.cxx|\.cc|\.c\+\+|\.hpp|\.hxx|\.hh|\.tpp|\.txx)$)delimiter";
    std::regex reg(regValue, regex_constants::icase);
    return std::regex_search(genericPath, reg);
}
