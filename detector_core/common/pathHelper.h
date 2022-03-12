//
// Created by Hualong Zhang on 2021/4/27.
//
#pragma once

#include <string>
#include <vector>
#include <filesystem>

class PathHelper final
{
public:
    static filesystem::path getCMakeListsDir()
    {
        filesystem::path detectorCommonPath(__FILE__);
        auto curDir = (detectorCommonPath.parent_path() / "../..");
#ifdef _WIN32
        //使用VS2019直接打开项目目录，__FILE__生成的是相对路径，如果把它转成绝对路径会发现，路径只想了main.cpp同级目录的out目录下，初步怀疑是VS的bug
        //detectorCommonPath = absolute(detectorCommonPath);
        //curDir = (detectorCommonPath.parent_path());
#endif
        return curDir.make_preferred().string();
    }

    static filesystem::path getParentPath(const string& filePath)
    {
        filesystem::path parentPath(filePath);
        return parentPath.parent_path().make_preferred();
    }

    static void removeDir(const string& filePath) {
        filesystem::remove_all(filePath);
    }
};
