#pragma once
#include <string>
#include <map>

typedef void* (*Constructor)();

class CObjectFactory final
{
public:
    static void registerClass(std::string className, Constructor constructor)
    {
        constructors()[className] = constructor;
    }

    static void* createObject(const std::string& className)
    {
        Constructor constructor = nullptr;
        if (constructors().find(className) != constructors().end())
            constructor = constructors().find(className)->second;

        if (constructor == nullptr)
            return nullptr;

        return (*constructor)();
    }

private:
    inline static std::map<std::string, Constructor>& constructors()
    {
        static std::map<std::string, Constructor> instance;
        return instance;
    }
};

#define REGISTER_CLASS(class_name) \
class class_name##Helper{ \
public: \
    class_name##Helper() \
    { \
        CObjectFactory::registerClass(#class_name, class_name##Helper::creatObjFunc); \
    } \
    static void* creatObjFunc() \
    { \
        return new class_name; \
    } \
 }; \
inline class_name##Helper class_name##helper;
