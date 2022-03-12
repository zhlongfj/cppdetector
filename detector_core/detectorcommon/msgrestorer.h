#pragma once
#include <string>
#include <vector>
#include "detectorcommon.h"
#include "jsonparsehelper.h"
#include "detectorhelp.h"

using namespace std;


class DETECTOR_EXPORT MsgRestorer final
{
public:
    void restoreMsgs(const string& configPath);

private:
    std::vector<tuple<std::string, std::string, std::string>> filterPaths(const vector<string>& filePaths);
    void restoreMsgToCode(const tuple<string, string, string>& codeContent, const DetectorRuleContents& detectorRuleContents);

    string getMsg(const string& className, const DetectorRuleContents& detectorRuleContents);

    DetectorRuleContents getDetectorRuleContents(const string& configPath);

    string prefix = "U8(";
    string postfix = "\"));";
};