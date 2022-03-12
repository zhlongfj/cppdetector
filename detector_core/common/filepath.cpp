//
// Created by Hualong Zhang on 2021/4/27.
//

#include <filesystem>
#include "filepath.h"

using namespace std;

vector<string> traverseRecursive(const std::string& path, std::function<bool(filesystem::directory_entry)> func)
{
    filesystem::path filePath(path);
    if (!exists(filePath)) {
        return vector<string>();
    }

    vector<std::string> filePaths;
    filesystem::directory_entry entry(filePath);
    if (entry.status().type() != filesystem::file_type::directory) {
        if (func(entry)) {
            filePaths.emplace_back(entry.path().generic_string());
        }
        return filePaths;
    }

    filesystem::directory_iterator fileList(filePath);
    for (const auto& item : fileList) {
        if (item.status().type() != filesystem::file_type::directory) {
            if (func(item)) {
                filePaths.emplace_back(item.path().generic_string());
            }
            continue;
        }

        auto ret = traverseRecursive(item.path().generic_string(), func);
        filePaths.insert(filePaths.end(), ret.begin(), ret.end());
    }
    return filePaths;
}

FilePath::FilePath(const std::string& path, std::function<bool(filesystem::directory_entry)> func) {
    m_filePaths = traverseRecursive(path, func);
}