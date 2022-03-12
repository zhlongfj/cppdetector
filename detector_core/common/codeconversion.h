//
// Created by Hualong Zhang on 2021/4/27.
//
#pragma once
#include <string>
#include "detector_global.h"
enum Encode { ANSI = 1, UTF16_LE, UTF16_BE, UTF8_BOM, UTF8 };

class DETECTOR_EXPORT CodeConversion final
{
public:
    static std::string gb2312_to_utf8(std::string const& strGb2312);
    static std::string utf8_to_gb2312(std::string const& strUtf8);
    static Encode checkCodeFormat(const uint8_t* data, size_t size);
};
