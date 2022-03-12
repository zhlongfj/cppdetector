#include <iostream>
#ifdef VCPKG
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include "client/windows/handler/exception_handler.h"
#elif defined(__APPLE__) && (defined(__GNUC__) || defined(__xlC__) || defined(__xlc__))
#include "client/mac/handler/exception_handler.h"
#endif
#endif

#include "iomanip"
#include "detector_core/detectorcommon/cpppath.h"
#include "detector_core/common/filehelp.h"

#include <filesystem>
#include <detectorcontext/detectorcontextcore.h>
#include "common/pathHelper.h"
#include "detectorcommon/msgrestorer.h"
#include "detectorcontext/singlethreaddetectorcontext.h"
#include "detectorcontext/multiprocessdetectorcontext.h"
#include "detectorcontext/multithreaddetectorcontext.h"

void  roundOff(const DetectorErrors& detectorErrors, filesystem::path resultDir)
{
    DetectorCommon detectorCommon;
    detectorCommon.printDetectorErrorToTerminal(detectorErrors);
    detectorCommon.generateGB2312Results(resultDir.generic_string());
    //导出配置
    auto contextCore = DetectorContextCore(unique_ptr<IFile>(make_unique<FileHelp>()));
    contextCore.init(contextCore.getDetectorRuleNames());
    detectorCommon.setDetectorRuleNames((resultDir / "detectorRuleNames.json").generic_string(), contextCore.getDetectorRuleNames());
    detectorCommon.setDetectorRuleContents((resultDir / "detectorRuleContents.json").generic_string(), contextCore.getDetectorRuleContents());
    //MsgRestorer().restoreMsgs((resultDir / "detectorRuleContents.json").string());
}

#ifdef VCPKG
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

static bool minidumpCallback(const wchar_t* dump_path, const wchar_t* id,
    void* context, EXCEPTION_POINTERS* exinfo,
    MDRawAssertionInfo* assertion,
    bool succeeded)
{
    if (succeeded) {
        std::wcout << "Mini Dump file: " << id << ".dump Path: " << dump_path << std::endl;
    }
    return succeeded;
}

static google_breakpad::ExceptionHandler eh(
    L".", NULL, minidumpCallback, NULL,
    google_breakpad::ExceptionHandler::HANDLER_ALL);

#else
static bool minidumpCallback(const char* dump_path, const char* id, void* context, bool succeeded)
{
    if (succeeded) {
        std::cout << "Mini Dump file: " << id << ".dump Path: " << dump_path << std::endl;
    }
    return succeeded;
}

static google_breakpad::ExceptionHandler eh(".", NULL, minidumpCallback, NULL, true, NULL);

#endif


void testCrash()
{
    //     int* ptr = NULL;
    //     *ptr = 0;
}

#endif

void Demo()
{
    unsigned int b = 10;
    //负数参与除法运算
    int c = -1 / b;
}

int main(int argc, char* argv[]) {
    //this_thread::sleep_for(chrono::seconds(10));
    auto begin = getCurrentMilliseconds();
    auto resultDir = PathHelper::getParentPath(argv[0]) / "detectorResult";
    if (argc >= 6)
    {
        resultDir = argv[5];
        std::cout << "resultDir: " << resultDir << std::endl;
    }
    if (!filesystem::exists(resultDir))
    {
        filesystem::create_directory(resultDir);
    }

    if (argc > 2)
    {
        //this_thread::sleep_for(chrono::seconds(10));
        if (strcmp("frommultiprocess", argv[1]) == 0)
        {
            string ruleNamePath;
            if (argc == 5)
            {
                ruleNamePath = argv[4];
                std::cout << ruleNamePath << std::endl;
                //argv[2]:header file
                //argv[3] source file
                SingleThreadDetectorContext(resultDir.string()).detectFromApp(argv[2], argv[3], ruleNamePath);
            }
        }

        shared_ptr<DetectorContext> context = nullptr;
        if (strcmp("multithread", argv[1]) == 0)
        {
            context = make_shared<MultiThreadDetectorContext>(resultDir.string());
        }
        else if (strcmp("multiprocess", argv[1]) == 0)
        {
            context = make_shared<MultiProcessDetectorContext>(resultDir.string(), argv[0]);
        }
        else
        {
            context = make_shared<SingleThreadDetectorContext>(resultDir.string());
        }

        auto codeDir = argv[2];
        std::cout << "codeDir: " << codeDir << std::endl;
        if (argc >= 4)
        {
            auto exceptionConfigPath = argv[3];
            std::cout << "exceptionConfigPath: " << exceptionConfigPath << std::endl;
            if (context->setExceptionConfigPath(exceptionConfigPath).empty())
            {
                return -1;
            }
        }
        std::string ruleNamePath;
        if (argc >= 5)
        {
            ruleNamePath = argv[4];
            std::cout << "ruleNamePath: " << ruleNamePath << std::endl;
        }

        DetectorErrors errors = context->detectWithRuleNamePath(codeDir, ruleNamePath);
        bool ret = context->existErrorResults(errors);
        DetectorCommon().printDetectorErrorToTerminal(errors);
        roundOff(errors, resultDir);
        std::cout << "run times: " << getCurrentMilliseconds() - begin << std::endl;
        return ret ? -1 : 0;
    }

    unique_ptr<DetectorContext> context = nullptr;
    context = (unique_ptr<DetectorContext>)make_unique<SingleThreadDetectorContext>(resultDir.string());
    context = (unique_ptr<DetectorContext>)make_unique<MultiThreadDetectorContext>(resultDir.string());

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    //define something for Windows (32-bit and 64-bit, this part is common)
    string codeDir = R"delimiter(F:\work\git\cppdetector\detector_core)delimiter";
    codeDir = R"ddd(F:\work\cppdetector\supporting\badcodesamples)ddd";
    //codeDir = R"ddd(F:\git\TscanCode\samples\cpp\suspiciousfor.cpp)ddd";
    //codeDir = R"delimiter(F:\work\git\viplexcore\src\libs\viplexcommon\tcp)delimiter";
    //codeDir = R"ddd(F:\work\git\cppdetector\supporting\badcodesamples)ddd";
    auto exceptionConfig = "F:\\work\\cppdetector\\supporting\\exceptionconfig.json";
#elif __APPLE__
    string codeDir = "/Users/hualongzhang/work/cppdetector/detector_core/";
    codeDir = "/Users/hualongzhang/work/cppdetector/supporting/badcodesamples";
    auto exceptionConfig = "/Users/hualongzhang/work/cppdetector/supporting/exceptionconfig.json";
#elif __linux__
    // linux
#elif __unix__ // all unices not caught above
    // Unix
#elif defined(_POSIX_VERSION)
    // POSIX
#else
    //#   error "Unknown compiler"
#endif

    if (context->setExceptionConfigPath(exceptionConfig).empty())
    {
        return -1;
    }
    filesystem::path dir(codeDir);
    auto codePath = dir.generic_string();
    DetectorErrors errors = context->detectAll(codePath);
    roundOff(errors, resultDir);
    bool ret = context->existErrorResults(errors);
    std::cout << "run times: " << getCurrentMilliseconds() - begin << std::endl;
    return ret ? -1 : 0;
}