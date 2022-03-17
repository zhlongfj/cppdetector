//
// Created by Hualong Zhang on 2021/4/26.
//
#pragma once
#include <vector>
#include <utility>
#include <string>
#include <map>
#include <memory>
#include <mutex>
#include "detectorcommon/detectorcommon.h"
#include <set>

using namespace std;

enum class ConcurrentType : int
{
    NoneConcurrent,
    MultiProcess,
    MultiThread
};
int64_t DETECTOR_EXPORT getCurrentMilliseconds();
class DetectorContextCore;
class DETECTOR_EXPORT DetectorContext {
public:
    DetectorContext(const string& resultDir, const string& resultName);
    virtual ~DetectorContext() {}
    DetectorErrors detectWithRuleNamePath(const string& codePath, const string& ruleNamePath);
    DetectorErrors detectWithRuleNames(const string& codePath, const DetectorRuleNames& detectorRuleNames);
    virtual DetectorRuleNames getDetectorRuleNames() = 0;
    vector<string> setExceptionConfigPath(const string& configPath);

    DetectorErrors detectAll(const string& codePath);

    bool existErrorResults(const DetectorErrors& errors);

private:
    virtual DetectorErrors getDetectorErrorsCore() = 0;
    virtual DetectorRuleContents getDetectorRuleContents() = 0;
    virtual pair<bool, string> init(const DetectorRuleNames& detectorRuleNames) = 0;
    bool detect(const string& codePath);
    uintmax_t getSizeFromPath(const string& filePath);
    virtual bool detectCore(const vector<CPPPathPair>& pathPairs) = 0;

    std::vector<CPPPathPair> makePathPairFromDir(const string& codePath);
    std::vector<CPPPathPair> makePathPairFromJSONPath(const string& jsonPath);
    std::vector<CPPPathPair> makePathPair(const vector<string>& codePaths);
    bool isExceptionPath(const string& path);

    DetectorErrors getDetectorErrors();

    vector<string> m_codePath;
    vector<string> m_exceptionPaths;

protected:
    string m_resultDir;
    string m_resultName;
    string m_resultNameZH;
    string m_ruleNamePath;
};
