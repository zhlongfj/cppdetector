#pragma once
#include "detectors/detector.h"
#include "inlinerule_tenlines.h"
#include "inlinerule_specialclassmethod.h"
#include "inlinerule_complexfunction.h"
#include "inlinerule_recursion.h"

//内联规则详见：
//    Google 开源项目风格指南：1.4. 内联函数：https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/headers/
//    编码规范，内联：https://www.jianshu.com/p/d08be89ee6af
class InlineDetector final : public Detector {
public:
    InlineDetector()
        :Detector("InlineDetector")
    {
    }

    vector<string> getRuleNames() override
    {
#ifdef WIN32
        return {
            GETRULENAMES(InlineRuleTenLines),
            GETRULENAMES(InlineRuleSpecialClassMethod),
            GETRULENAMES(InlineRuleComplexFunction),
            GETRULENAMES(InlineRuleRecursion)
        };
#else
        return {
            "InlineRuleTenLines",
            "InlineRuleSpecialClassMethod",
            "InlineRuleComplexFunction",
            "InlineRuleRecursion"
        };
#endif
    }
};

REGISTER_CLASS(InlineDetector)