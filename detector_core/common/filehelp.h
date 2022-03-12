//
// Created by Hualong Zhang on 2021/4/27.
//
#pragma once
#include "detector_global.h"
#include "ifile.h"

class DETECTOR_EXPORT FileHelp final : public IFile {
public:
    bool write(const std::string& filePath, const std::string& content) override;
    std::string parse(const std::string& filePath) override;
    std::vector<std::string> getLines() override;
};
