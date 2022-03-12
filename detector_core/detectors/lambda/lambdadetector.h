//
// Created by Hualong Zhang on 2021/4/26.
//

#pragma once
#include "detectors/detector.h"
#include "lambdarule_catchbyreference.h"
#include "../../common/reflecter.h"

class LambdaDetector final : public Detector {
public:
    LambdaDetector()
        :Detector("LambdaDetector")
    {
    }

    vector<string> getRuleNames() override
    {
#ifdef WIN32
        return {
            GETRULENAMES(LambdaRuleCatchByReference)
        };
#else
        return {
            "LambdaRuleCatchByReference"
        };
#endif
    }
};

REGISTER_CLASS(LambdaDetector)