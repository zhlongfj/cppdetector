//
// Created by Hualong Zhang on 2021/4/26.
//
#pragma once
#include <string>
#include <vector>

using namespace std;

class DETECTOR_EXPORT IDetector {
public:
    explicit IDetector(const string& name) :m_name(name) {}
    virtual ~IDetector() {}
    virtual bool detect(const string& content, const string& path) = 0;
    virtual bool detect(const string& content, const ErrorFile& errorFile) = 0;
    virtual void resetData() {}
    string getName() const { return m_name; }
protected:
    string m_name;
};
