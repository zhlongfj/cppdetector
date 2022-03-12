//
// Created by Hualong Zhang on 2021/4/27.
//
#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <functional>
#include "ipath.h"

class FilePath final : public IPath {
public:
    FilePath(const std::string& path, std::function<bool(std::filesystem::directory_entry)> func);
};
