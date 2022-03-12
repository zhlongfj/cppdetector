//
// Created by Hualong Zhang on 2021/4/27.
//

#pragma once

#include <string>
#include "detector_global.h"
#include "common/ipath.h"

class DETECTOR_EXPORT CPPPath final : public IPath {
public:
    explicit CPPPath(const std::string& path);
    static bool isCPPCodeFile(const std::string& filePath);
};
