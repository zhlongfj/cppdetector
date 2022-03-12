//
// Created by Hualong Zhang on 2021/4/26.
//
#pragma once
#include "detector_global.h"
#include <vector>
#include <utility>
#include <string>
#include <map>
#include <memory>
#include "detectors/detector.h"

using namespace std;

class IPath;
class IFile;
class CodeFileter;
class DETECTOR_EXPORT DetectorContextCore final {
public:
    explicit DetectorContextCore(unique_ptr<IFile> pFile);
    ~DetectorContextCore();
    DetectorRuleName getDetectorName(unique_ptr<Detector> detector);
    pair<bool, string> init(const DetectorRuleNames& detectorRuleNames);

    DetectorRuleNames getDetectorRuleNames();

    bool detect(const CPPPathPair& pathPair);
    DetectorRuleContents getDetectorRuleContents();
    DetectorErrors getDetectorErrors() { return m_detectorErrors; }

private:
    vector<unique_ptr<Detector>> m_detectors;
    DetectorErrors m_detectorErrors;
    void detectWithDetectors(const CPPPathPair& pathPair);
    void detectWithDetectors(const string& filePath);
    unique_ptr<IFile> m_pFile;
    unique_ptr<CodeFilter> m_codeFileter;
};
