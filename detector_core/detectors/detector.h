//
// Created by Hualong Zhang on 2021/4/26.
//
#pragma once
#include <string>
#include <map>
#include <memory>
#include "detectorcommon/detectorcommon.h"
#include "rule.h"
#include "idetector.h"
#include "../common/reflecter.h"
#include <execution>

//preprocessing token include:
//header names, identiﬁers, preprocessing numbers, character constants, string literals, punctuators,
//and single non-white-space characters that do not lexically match the other preprocessing token categories.
#ifdef WIN32
#define GETRULENAMES(ruleName) ruleName##().getName()
#endif

using namespace std;

class Detector : public IDetector {
public:
    using IDetector::IDetector;
    virtual ~Detector() {}
    void resetData() override {
        IDetector::resetData();
        for (const auto& item : m_detectorRules)
        {
            item->resetData();
        }
    }
    bool detect(const string& content, const string& path) override
    {
        bool find = false;
        for (auto element : m_detectorRules)
        {
            if (element->detect(content, path))
            {
                find = true;
            }
        }
        return find;
    }

    bool detect(const string& content, const ErrorFile& errorFile) override
    {
        bool find = false;
        for (auto element : m_detectorRules)
        {
            if (element->detect(content, errorFile))
            {
                find = true;
            }
        }
        return find;
    }

    RuleContents getRuleContents() {
        RuleContents ruleContents(m_detectorRules.size());
        transform(m_detectorRules.begin(), m_detectorRules.end(), ruleContents.begin(), [](shared_ptr<IRule> item) {return item->getRuleContent(); });

        return ruleContents;
    }

    shared_ptr<DetectorError> getDetectorError() {
        vector<shared_ptr<RuleError>> ruleErrors;
        for (const auto& item : m_detectorRules)
        {
            auto ret = item->getRuleErrors();
            if (ret.empty())
            {
                continue;
            }

            ruleErrors.insert(ruleErrors.end(), ret.begin(), ret.end());
        }

        return make_unique<DetectorError>(m_name, ruleErrors);
    }

    virtual vector<string> getRuleNames() = 0;

    pair<bool, string> init(const vector<string>& ruleNames)
    {
        for (const auto& item : ruleNames)
        {
            Rule* pRule = static_cast<Rule*>(CObjectFactory::createObject(item));
            if (pRule == nullptr)
            {
                return { false, "create rule: " + item + " error, please check rule name or REGISTER_CLASS(ruleName)" };
            }

            m_detectorRules.emplace_back(std::move(pRule));
        }

        return { true, "" };
    }

protected:
    vector<shared_ptr<IRule>> m_detectorRules;
};
