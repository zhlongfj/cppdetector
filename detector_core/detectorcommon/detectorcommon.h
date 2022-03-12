#pragma once
#include "detector_global.h"
#include <string>
#include <map>
#include <unordered_map>
#include <utility>
#include <vector>
#include <memory>
#include <set>

using namespace std;
enum class ErrorPriority : int {
    Critical = 1,
    Error,
    Warning,
    Suggest
};

struct RuleContent
{
    ErrorPriority priority = ErrorPriority::Suggest;
    string rule;
    string msg;
    RuleContent(ErrorPriority priority, const string& rule, const string& msg) : priority(priority), rule(rule), msg(msg) {}
    ~RuleContent() {}
};

struct CPPPathPair
{
    string header;
    string source;
    CPPPathPair() {}
    CPPPathPair(const string& header, const string& source) :header(header), source(source) {}
};

struct ErrorFile {
    int line = 0;
    string path;
    ErrorFile()
        : line(0), path("") {};
    ErrorFile(const int line, const string& path)
        : line(line), path(path) {};
    ErrorFile(const ErrorFile& errorFile) {
        this->path = errorFile.path;
        this->line = errorFile.line;
    };
    void resetData()
    {
        line = 0;
        path.clear();
    }
};

struct RuleError {
    shared_ptr<RuleContent> ruleContent;
    ErrorFile errorFile;
    RuleError(shared_ptr<RuleContent> ruleContent, const ErrorFile& errorFile)
        : ruleContent(ruleContent), errorFile(errorFile) {};
};

struct DetectorError final {
    string detector;
    vector<shared_ptr<RuleError>> ruleErrors;
    DetectorError(const string& detector, const vector<shared_ptr<RuleError>>& ruleErrors)
        : detector(detector), ruleErrors(ruleErrors) {};
    ~DetectorError() {};
};

using RuleContents = vector<shared_ptr<RuleContent>>;
using DetectorRuleContents = unordered_map<string, RuleContents>;
using DetectorRuleName = pair<string, vector<string>>;
using DetectorRuleNames = map<string, vector<string>>;
using DetectorErrors = map<string, vector<shared_ptr<RuleError>>>;

class DETECTOR_EXPORT DetectorCommon final
{
public:
    DetectorCommon();
    DetectorRuleNames getDetectorRuleNames(const string& configPath);
    void setDetectorRuleNames(const string& configPath, const DetectorRuleNames& detectorRuleNames);
    void setDetectorRuleContents(const string& configPath, const DetectorRuleContents& detectorRuleContents);
    void setDetectorErrors(const string& configPath, const DetectorErrors& detectorErrors);
    void printDetectorErrorToTerminal(const DetectorErrors& detectorErrors);
    DetectorErrors getDetectorErrors(const string& configPath);
    vector<string> getPathsFromConfigPath(const string& configPath);
    void generateGB2312Results(const string& configPath);

private:
    map<string, map<string, string>> m_errorMsgs;
};