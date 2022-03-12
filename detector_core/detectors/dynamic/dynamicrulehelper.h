#pragma once
#include <utility>
#include <string>

class DynamicRuleHelper final
{
public:
    static std::pair<std::string, std::string> findExportedClass(const std::string& code);
    
    static bool findClassDomain(const std::string& code, const std::string& className);
};