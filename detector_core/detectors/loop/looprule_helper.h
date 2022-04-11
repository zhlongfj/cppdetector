#pragma once
#include "../rule.h"
#include "../../common/reflecter.h"

using VariableInFor = pair<std::string, set<std::string>>;
class DETECTOR_EXPORT LoopRuleHelper final {
public:
    static bool findNotAutoFromFor(const std::string& code);

    static VariableInFor getVariablesFromFor(const std::string& code);

    static bool isValid(const std::string& code, std::string& variable);
};
