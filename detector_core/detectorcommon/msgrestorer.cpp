#include "msgrestorer.h"
#include "../3rdparty/json.hpp"
#include "common/pathHelper.h"
#include "cpppath.h"
#include "common/filehelp.h"
#include <iostream>
using namespace std; 
using namespace nlohmann;

void MsgRestorer::restoreMsgs(const string& configPath)
{
    auto detectorsDir = PathHelper::getCMakeListsDir() / "detector_core/detectors";
    CPPPath cppPath(detectorsDir.string());

    DetectorRuleContents detectorRuleContents = getDetectorRuleContents(configPath);
    auto filePaths = filterPaths(cppPath.getFilePaths());

    for (const auto& item : filePaths) {
        restoreMsgToCode(item, detectorRuleContents);
    }
}

std::vector<tuple<std::string, std::string, std::string>> MsgRestorer::filterPaths(const vector<string>& filePaths)
{
    vector<tuple<string, string, string>> codeContents;
    for (const auto& item : filePaths) {
        auto datas = FileHelp().parse(item);
        auto ret = DetectorHelper::check(datas, "Rule\\(\"(\\w+)\"\\)");
        if (ret.empty())
        {
            continue;
        }
        codeContents.emplace_back(ret[1], item, datas);
    }
    return codeContents;
}

void MsgRestorer::restoreMsgToCode(const tuple<string, string, string>& codeContent, const DetectorRuleContents& detectorRuleContents)
{
    auto [className, filePath, datas] = codeContent;
    auto msg = getMsg(className, detectorRuleContents);
    auto start = datas.find(prefix);
    auto end = datas.find(postfix);
    if (start == string::npos
        || end == string::npos)
    {
        auto msg = "could not find: \"U8(\"*\");\" in file: " + filePath;
        std::cout << msg << std::endl;
        throw msg;
    }

    auto replacedStart = start + prefix.size() + 1;
    datas = datas.replace(replacedStart, end - replacedStart, msg);
    FileHelp().write(filePath, datas);
}

std::string MsgRestorer::getMsg(const string& className, const DetectorRuleContents& detectorRuleContents)
{
    for (const auto& item : detectorRuleContents)
    {
        const RuleContents& ruleContents = item.second;
        for (const auto& item1 : ruleContents)
        {
            if (item1->rule == className)
            {
                return item1->msg;
            }
        }
    }
    auto msg = "could not find className: " + className;
    std::cout << msg << std::endl;
    throw msg;
}

DetectorRuleContents MsgRestorer::getDetectorRuleContents(const string& configPath)
{
    auto fileData = FileHelp().parse(configPath);
    json jData = json::parse(fileData);
    return JSONParseHelper().fromJSON(jData);
}

