#pragma once
#include "../3rdparty/json.hpp"

using namespace nlohmann;

class JSONParseHelper final
{
public:

    json toJSON(shared_ptr<RuleContent> ruleContent)
    {
        json jRuleContent = toJSON_RuleContentCore(ruleContent);
        jRuleContent["msg"] = ruleContent->msg;
        jRuleContent["msg_zh"] = ruleContent->msg_zh;
        return jRuleContent;
    }

    json toJSON_RuleContentEN(shared_ptr<RuleContent> ruleContent)
    {
        json jRuleContent = toJSON_RuleContentCore(ruleContent);
        jRuleContent["msg"] = ruleContent->msg;
        return jRuleContent;
    }

    json toJSON_RuleContentZH(shared_ptr<RuleContent> ruleContent)
    {
        json jRuleContent = toJSON_RuleContentCore(ruleContent);
        jRuleContent["msg_zh"] = ruleContent->msg_zh;
        return jRuleContent;
    }

    json toJSON_RuleContentCore(shared_ptr<RuleContent> ruleContent)
    {
        json jRuleContent;
        jRuleContent["rule"] = ruleContent->rule;
        jRuleContent["priority"] = ruleContent->priority;
        return jRuleContent;
    }

    shared_ptr<RuleContent> fromJSONRuleContent(json jData)
    {
        return make_shared<RuleContent>(
            (ErrorPriority)jData["priority"].get<int>(),
            jData["rule"].get<string>(),
            jData["msg"].get<string>(),
            jData["msg_zh"].get<string>());
    }

    DetectorRuleContents fromJSON(json jData)
    {
        DetectorRuleContents detectorRuleContents;
        for (auto iter = jData.begin(); iter != jData.end(); ++iter) {
            RuleContents ruleContents;
            auto jRuleContents = iter.value();
            for (auto iter1 = jRuleContents.begin(); iter1 != jRuleContents.end(); ++iter1) {
                ruleContents.emplace_back(fromJSONRuleContent(*iter1));
            }
            detectorRuleContents.insert({ iter.key(), ruleContents });
        }

        return detectorRuleContents;
    }

    json toJSON(const ErrorFile& errorFile)
    {
        json jErrorFile;
        jErrorFile["path"] = errorFile.path;
        jErrorFile["line"] = errorFile.line;
        return jErrorFile;
    }

    ErrorFile fromJSONErrorFile(json jData)
    {
        return ErrorFile(
            jData["line"].get<int>(),
            jData["path"].get<string>());
    }

    json toJSONEN(shared_ptr<RuleError> ruleError)
    {
        json jRuleError;
        jRuleError["rulecontent"] = toJSON_RuleContentEN(ruleError->ruleContent);
        jRuleError["errorfile"] = toJSON(ruleError->errorFile);
        return jRuleError;
    }

    json toJSONZH(shared_ptr<RuleError> ruleError)
    {
        json jRuleError;
        jRuleError["rulecontent"] = toJSON_RuleContentZH(ruleError->ruleContent);
        jRuleError["errorfile"] = toJSON(ruleError->errorFile);
        return jRuleError;
    }

    shared_ptr<RuleError> fromJSONRuleError(json jData)
    {
        return make_shared<RuleError>(
            fromJSONRuleContent(jData["rulecontent"]),
            fromJSONErrorFile(jData["errorfile"]));
    }
};
