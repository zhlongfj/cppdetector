//
// Created by Hualong Zhang on 2021/4/26.
//
#pragma once
#include <string>
#include <map>
#include "detectorcommon/detectorcommon.h"
#include "idetector.h"
#include <common/stringhelper.h>
#include "detectorcommon/codefilter.h"
#include <filesystem>

using namespace std;

class DETECTOR_EXPORT IRule : public IDetector {
public:
    using IDetector::IDetector;
    vector<shared_ptr<RuleError>> getRuleErrors()
    {
        auto ruleErrors = m_ruleErrors;
        m_ruleErrors.clear();
        return ruleErrors;
    }
    shared_ptr<RuleContent> getRuleContent() const { return m_ruleContent; }

    void storeRuleError(const ErrorFile& errorFile) {
        auto path = filesystem::path(errorFile.path).u8string();
        ErrorFile errorFileTmp(errorFile.line, path);
        m_ruleErrors.emplace_back(make_shared<RuleError>(m_ruleContent, errorFileTmp));
    }
    virtual ~IRule() {}
protected:
    vector<shared_ptr<RuleError>> m_ruleErrors;
    shared_ptr<RuleContent> m_ruleContent;
};

class DETECTOR_EXPORT Rule : public IRule {
public:
    using IRule::IRule;
    virtual ~Rule() {}
    virtual bool detect(const string& content, const string& path) override {
        CodeFilter codeFilter;
        auto lines = StringHelper(content).getLines();
        bool ret = false;
        for (auto i = 0; i < lines.size(); ++i) {
            auto code = codeFilter.filterCode(lines[i]);
            if (code.empty())
            {
                continue;
            }

            if (detect(code, ErrorFile{i + 1, path}))
            {
                ret = true;
            }
        }
        return ret;
    }

    bool detect(const string& content, const ErrorFile& errorFile) override
    {
        return detectCore(content, errorFile);
    }

    virtual bool detectCore(const string& content, const ErrorFile& errorFile) = 0;

    virtual void resetData() override
    {
        IRule::resetData();
        codeFilter.resetData();
    }

private:
    CodeFilter codeFilter;
};
