//
// Created by Hualong Zhang on 2021/4/26.
//

#include "detectorcontextcore.h"
#include "common/filehelp.h"
#include <filesystem>
#include "common/reflecter.h"
#include "detectors/pointer/pointerdetector.h"
#include "detectors/dynamic/dynamicdetector.h"
#include "detectors/lambda/lambdadetector.h"
#include "detectors/singleton/singletondetector.h"
#include "detectors/array/arraydetector.h"
#include "detectors/memleak/memleakdetector.h"
#include "detectors/operation/operationdetector.h"
#include "detectors/confused/confuseddetector.h"
#include "detectors/logic/logicdetector.h"
#include "detectors/uninit/uninitdetector.h"
#include "detectors/iterator/iteratordetector.h"
#include "detectors/loop/loopdetector.h"
#include "detectors/variable/variabledetector.h"
#include "detectors/sizeof/sizeofdetector.h"
#include "common/stringhelper.h"
#include "detectorcommon/detectorcommon.h"
#include "detectorcommon/codefilter.h"
#include "detectors/inline/inlinedetector.h"
#include "detectors/accesscontrol/accesscontroldetector.h"
#include "detectors/class/classdetector.h"

using namespace std;

#ifdef WIN32
#define GETDETECTORNAME(DetectorClassName) {DetectorClassName##().getName(), DetectorClassName##().getRuleNames()}
#endif

DetectorContextCore::DetectorContextCore(unique_ptr<IFile> pFile)
    : m_pFile(move(pFile))
    , m_codeFileter(make_unique<CodeFilter>()) {
}

DetectorContextCore::~DetectorContextCore() = default;

DetectorRuleName DetectorContextCore::getDetectorName(unique_ptr<Detector> detector)
{
    return { detector->getName(), detector->getRuleNames() };
}

std::pair<bool, std::string> DetectorContextCore::init(const DetectorRuleNames& detectorRuleNames)
{
    for (const auto& item : detectorRuleNames)
    {
        Detector* pDetector = static_cast<Detector*>(CObjectFactory::createObject(item.first));
        if (pDetector == nullptr)
        {
            return { false, "create detector: " + item.first + " error, please check detector name or REGISTER_CLASS(detectorName)" };
        }
        unique_ptr<Detector> detector = unique_ptr<Detector>(pDetector);
        auto ret = pDetector->init(item.second);
        if (!ret.first)
        {
            return ret;
        }

        m_detectors.emplace_back(std::move(detector));
    }

    return { true, "" };
}

DetectorRuleNames DetectorContextCore::getDetectorRuleNames()
{
#ifdef WIN32
    return {
        GETDETECTORNAME(LambdaDetector),
        GETDETECTORNAME(SingletonDetector),
        GETDETECTORNAME(DynamicDetector),
        GETDETECTORNAME(PointerDetector),
        GETDETECTORNAME(ArrayDetector),
        GETDETECTORNAME(MemLeakDetector),
        GETDETECTORNAME(SizeofDetector),
        GETDETECTORNAME(OperationDetector),
        GETDETECTORNAME(ConfusedDetector),
        GETDETECTORNAME(LogicDetector),
        GETDETECTORNAME(UninitDetector),
        GETDETECTORNAME(IteratorDetector),
        GETDETECTORNAME(LoopDetector),
        GETDETECTORNAME(VariableDetector),
        GETDETECTORNAME(InlineDetector),
        GETDETECTORNAME(AccessControlDetector),
        GETDETECTORNAME(ClassDetector)
    };
#else
    return {
        getDetectorName(unique_ptr<Detector>(make_unique<LambdaDetector>())),
        getDetectorName(unique_ptr<Detector>(make_unique<SingletonDetector>())),
        getDetectorName(unique_ptr<Detector>(make_unique<DynamicDetector>())),
        getDetectorName(unique_ptr<Detector>(make_unique<PointerDetector>())),
        getDetectorName(unique_ptr<Detector>(make_unique<ArrayDetector>())),
        getDetectorName(unique_ptr<Detector>(make_unique<MemLeakDetector>())),
        getDetectorName(unique_ptr<Detector>(make_unique<SizeofDetector>())),
        getDetectorName(unique_ptr<Detector>(make_unique<OperationDetector>())),
        getDetectorName(unique_ptr<Detector>(make_unique<ConfusedDetector>())),
        getDetectorName(unique_ptr<Detector>(make_unique<LogicDetector>())),
        getDetectorName(unique_ptr<Detector>(make_unique<UninitDetector>())),
        getDetectorName(unique_ptr<Detector>(make_unique<IteratorDetector>())),
        getDetectorName(unique_ptr<Detector>(make_unique<LoopDetector>())),
        getDetectorName(unique_ptr<Detector>(make_unique<VariableDetector>())),
        getDetectorName(unique_ptr<Detector>(make_unique<InlineDetector>())),
        getDetectorName(unique_ptr<Detector>(make_unique<AccessControlDetector>())),
        getDetectorName(unique_ptr<Detector>(make_unique<ClassDetector>()))
    };
#endif
}

bool DetectorContextCore::detect(const CPPPathPair& pathPair)
{
    detectWithDetectors(pathPair);

    for (const auto& item : m_detectors) {
        auto detectorError = item->getDetectorError();
        if (detectorError->ruleErrors.empty())
        {
            continue;
        }
        if (m_detectorErrors.find(detectorError->detector) == m_detectorErrors.end())
        {
            m_detectorErrors.insert({ detectorError->detector, detectorError->ruleErrors });
            continue;
        }
        auto& ruleErrors = m_detectorErrors[detectorError->detector];
        ruleErrors.insert(ruleErrors.end(), detectorError->ruleErrors.begin(), detectorError->ruleErrors.end());
    }

    return true;
}

DetectorRuleContents DetectorContextCore::getDetectorRuleContents()
{
    DetectorRuleContents detectorRuleContents;
    for (const auto& item : m_detectors)
    {
        detectorRuleContents.insert({ item->getName(), item->getRuleContents() });
    }

    return detectorRuleContents;
}

void DetectorContextCore::detectWithDetectors(const CPPPathPair& pathPair) {
    if (!pathPair.header.empty())
    {
        detectWithDetectors(pathPair.header);
    }

    if (!pathPair.source.empty())
    {
        detectWithDetectors(pathPair.source);
    }

    for (const auto& item : m_detectors) {
        item->resetData();
    }
    m_codeFileter->resetData();
}

void DetectorContextCore::detectWithDetectors(const string& filePath)
{
    filesystem::path path(filePath);
    auto content = m_pFile->parse(filePath);
    auto lines = StringHelper(content).getLines();
    for (auto i = 0; i < lines.size(); ++i) {
        auto code = m_codeFileter->filterCode(lines[i]);
        if (code.empty())
        {
            continue;
        }
        auto errorFile = ErrorFile{ i + 1, filePath };
        for (const auto& item : m_detectors) {
            item->detect(code, errorFile);
        }
    }
}