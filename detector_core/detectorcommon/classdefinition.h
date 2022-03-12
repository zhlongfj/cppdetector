#pragma once
#include <string>
#include "detectorhelp.h"
#include "common/stringhelper.h"
#include <utility>
#include <map>
#include <iostream>
#include <functional>

using namespace std;

enum class DETECTOR_EXPORT AccessControl
{
    PUBLIC,
    PROTECTED,
    PRIVATE
};

struct DETECTOR_EXPORT ClassInfo
{
    string className;
    string spaceBeforeVariable;
    string accessControl = "private:";
    bool isStruct = false;
    ClassInfo(const string& className, const string& spaceBeforeVariable) : className(className), spaceBeforeVariable(spaceBeforeVariable) {}
};

class DETECTOR_EXPORT ClassDefinition final
{
public:
    bool inClassDefinition(const string& content);

    bool isStruct();

    pair<bool, string> isConstructor(const string& content);

    pair<bool, string> isAssignment(const string& content);

    int getReferenceCount(const string& content, const string& className);

    pair<bool, string> isDestructor(const string& content);

    bool isVirtual(const string& content);

    AccessControl getAccessControl(const string& content);

    void resetData();

private:
    pair<bool, string> check(const string& content, std::function<string(const string&)> func);
    vector<shared_ptr<ClassInfo>> m_classInfos;
    shared_ptr<ClassInfo> m_classInfo;
    const std::map<std::string, AccessControl> m_accessControls = {
        {"public:", AccessControl::PUBLIC},
        {"protected:", AccessControl::PROTECTED },
        {"private:", AccessControl::PRIVATE} };
};