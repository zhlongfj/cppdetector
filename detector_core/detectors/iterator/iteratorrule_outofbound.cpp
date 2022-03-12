#include "iteratorrule_outofbound.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"
#include "detectorcommon/fordefinition.h"

IteratorRuleOutOfBound::IteratorRuleOutOfBound() : Rule("IteratorRuleOutOfBound") {
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Critical, m_name,
        U8("容器迭代器越界"));
}

bool IteratorRuleOutOfBound::detectCore(const string& code, const ErrorFile& errorFile) {
    if (code.find("=") != string::npos
        && (code.find("size") != string::npos || code.find("length") != string::npos)) {
        //Performance optimization, filter mismatches
        if (auto ret = DetectorHelper::check(code,
            R"delimiter((\w+)\s*=\s*\w+(\.|->)(size|length)\(\))delimiter"); !ret.empty()) {
            //check "auto ss = foo.size();"
            m_sizeVariable = ret[1];
            return false;
        }
    }

    if (code.find("<=") == string::npos) {
        return false;
    }

    ForDefinition forDefinition;
    if (!forDefinition.isFor(code)
        || forDefinition.comparationSymbol().find("=") == string::npos)
    {
        return false;
    }
    
    if (forDefinition.endCondition().find("size()") == string::npos
        && forDefinition.endCondition().find("length()") == string::npos
        && forDefinition.endCondition() != m_sizeVariable)
    {
        return false;
    }
    
    //check "for (unsigned int ii = 0; ii <= foo.size(); ++ii)" or "for (unsigned int ii = 0; ii <= ss; ++ii)"
    storeRuleError(errorFile);
    return true;
}

void IteratorRuleOutOfBound::resetData() {
    Rule::resetData();
    m_sizeVariable.clear();
}

