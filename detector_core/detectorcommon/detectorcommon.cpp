#include "detectorcommon.h"
#include "../3rdparty/json.hpp"
#include <iosfwd>
#include <sstream>
#include <iostream>
#include "common/filehelp.h"
#include <memory>
#include "cpppath.h"
#include "common/pathHelper.h"
#include "jsonparsehelper.h"
#include "common/stringhelper.h"
#include <filesystem>
#include "common/codeconversion.h"

using namespace std;

DetectorCommon::DetectorCommon()
{
    json jsons;
    for (const auto& item : m_errorMsgs)
    {
        auto detectorType = item.first;
        jsons[detectorType];
        for (const auto& item1 : item.second)
        {
            auto ruleType = item1.first;
            jsons[detectorType][ruleType] = item1.second;
        }
    }

    map<string, map<string, string>> errorMsgs;
    for (auto i = jsons.begin(); i != jsons.end(); ++i) {
        auto detectorType = i.key();
        errorMsgs[detectorType];
        for (auto it = i.value().begin(); it != i.value().end(); ++it)
        {
            auto ruleType = it.key();
            errorMsgs[detectorType][ruleType] = it.value().get<string>();
        }
    }

    for (const auto& item : errorMsgs)
    {
        std::cout << item.first << std::endl;
        for (const auto& item1 : item.second)
        {
            cout << "    " << item1.first << ":" << item1.second << endl;
        }
    }

    std::cout << std::endl;
}

DetectorRuleNames DetectorCommon::getDetectorRuleNames(const string& configPath)
{
    auto config = FileHelp().parse(configPath);
    if (config.empty())
    {
        return DetectorRuleNames();
    }

    json jsons = json::parse(config);
    DetectorRuleNames detectorRuleNames;
    for (auto it = jsons.begin(); it != jsons.end(); ++it)
    {
        auto detectorName = it.key();
        detectorRuleNames.insert({ detectorName, vector<string>() });
        auto ruleNames = it.value();
        for (auto it1 = ruleNames.begin(); it1 != ruleNames.end(); ++it1)
        {
            detectorRuleNames[detectorName].emplace_back(it1->get<string>());
        }
    }
    return detectorRuleNames;
}

void DetectorCommon::setDetectorRuleNames(const string& configPath, const DetectorRuleNames& detectorRuleNames)
{
    std::size_t ruleSize = 0;
    json data;
    for (const auto& item : detectorRuleNames)
    {
        ruleSize += item.second.size();
        data[item.first] = item.second;
    }
    std::cout << "rule size: " << ruleSize << std::endl;
    FileHelp().write(configPath, data.dump());
}

void DetectorCommon::setDetectorRuleContents(const string& configPath, const DetectorRuleContents& detectorRuleContents)
{
    map<string, json> datas;
    transform(detectorRuleContents.begin(), detectorRuleContents.end(), std::inserter(datas, datas.end()), [](const pair<string, RuleContents>& item) {
        auto sourceRuleContents = item.second;
        vector<json> ruleContents(sourceRuleContents.size());
        transform(sourceRuleContents.begin(), sourceRuleContents.end(), ruleContents.begin(), [](const auto& item1) {return JSONParseHelper().toJSON(item1); });
        return make_pair(item.first, ruleContents);
        });
    json data = datas;
    FileHelp().write(configPath, data.dump());
}

void DetectorCommon::setDetectorErrors(const string& configPath, const DetectorErrors& detectorErrors)
{
    map<string, json> datas;
    transform(detectorErrors.begin(), detectorErrors.end(), std::inserter(datas, datas.end()), [](const pair<string, vector<shared_ptr<RuleError>>>& item) {
        auto sourceRuleErrors = item.second;
        vector<json> ruleErrors(sourceRuleErrors.size());
        transform(sourceRuleErrors.begin(), sourceRuleErrors.end(), ruleErrors.begin(), [](const auto& element) {
            return JSONParseHelper().toJSON(element); });
        return make_pair(item.first, ruleErrors);
        });

    json data = datas;
    FileHelp().write(configPath, data.dump());
}

void DetectorCommon::printDetectorErrorToTerminal(const DetectorErrors& detectorErrors)
{
    int i = 0;
    for (const auto& item : detectorErrors) {
        auto ruleErrors = item.second;
        for (const auto& element : ruleErrors)
        {
            auto msg = element->ruleContent->msg;
            auto path = element->errorFile.path;
#ifdef _WIN32
            //windows平台下，控制台输出不支持U8，需要转换成GB2312
            msg = CodeConversion::utf8_to_gb2312(msg);
            path = CodeConversion::utf8_to_gb2312(path);
#endif
            i++;
            std::cout << msg << " " << std::left << std::setw(4)
                << element->errorFile.line << " " << path << std::endl;
        }
    }
    std::cout << "error size: " << i << std::endl;
}

DetectorErrors DetectorCommon::getDetectorErrors(const string& configPath)
{
    auto config = FileHelp().parse(configPath);
    if (config.empty())
    {
        return DetectorErrors();
    }

    json jsons = json::parse(config);
    DetectorErrors detectorErrors;
    for (auto it = jsons.begin(); it != jsons.end(); ++it)
    {
        auto detectorName = it.key();
        detectorErrors.insert({ detectorName, vector<shared_ptr<RuleError>>() });
        auto jsonRuleErrors = it.value();
        for (auto it1 = jsonRuleErrors.begin(); it1 != jsonRuleErrors.end(); ++it1)
        {
            detectorErrors[detectorName].emplace_back(JSONParseHelper().fromJSONRuleError(*it1));
        }
    }
    return detectorErrors;
}

vector<string> DetectorCommon::getPathsFromConfigPath(const string& configPath)
{
    auto config = FileHelp().parse(configPath);
    if (config.empty())
    {
        string message = "file: " + configPath + " is not exist or file is empty!";
        std::cout << message << std::endl;
        return vector<string>();
    }
    config = StringHelper(config).replace("\\", "/");
    vector<string> exceptionPaths;
    try
    {
        json jsons = json::parse(config);
        for (auto iter = jsons.begin(); iter != jsons.end(); ++iter)
        {
            auto codeFile = iter.value().get<string>();
            filesystem::path dir(codeFile);
            auto codePath = dir.generic_string();;
            exceptionPaths.emplace_back(codePath);
        }
    }
    catch (nlohmann::detail::parse_error e)
    {
        string message = "the contents of file: " + configPath + " is not json(path array)";
        std::cout << message << std::endl;
        std::cout << e.what() << std::endl;
    }

    return exceptionPaths;
}

void DetectorCommon::generateGB2312Results(const string& resultDir)
{
    filesystem::path resultsPath(resultDir);
    auto results = FileHelp().parse((resultsPath / "results.json").generic_string());
    auto resultsGB2321 = CodeConversion::utf8_to_gb2312(results);
    auto resultsGB2312Path = (resultsPath / "results_gb2321.json").generic_string();
    FileHelp().write(resultsGB2312Path, resultsGB2321);
}
