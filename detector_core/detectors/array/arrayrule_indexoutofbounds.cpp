#include "arrayrule_indexoutofbounds.h"
#include "detectorcommon/detectorhelp.h"
#include "../../common/stringhelper.h"
#include "arrayrulehelper.h"

ArrayRuleIndexOutOfBounds::ArrayRuleIndexOutOfBounds()
    : ArrayRuleIndexOutOfBounds(make_unique<ArrayRuleHelper>())
{
}

ArrayRuleIndexOutOfBounds::ArrayRuleIndexOutOfBounds(std::unique_ptr<ArrayRuleHelper> helper) : Rule("ArrayRuleIndexOutOfBounds")
    , m_helper(move(helper))
{
    m_ruleContent = make_shared<RuleContent>(ErrorPriority::Critical, m_name,
        "Array index may cause out-of-bounds access. "\
        "Please check whether the maximum value of the array index is greater than the array's length or less than 0.",
        U8("数组下标可能产生越界访问，请检查数组下标的最大取值是否超过了数组长度或小于0"));
}

ArrayRuleIndexOutOfBounds::~ArrayRuleIndexOutOfBounds() = default;

bool ArrayRuleIndexOutOfBounds::detectCore(const string &code, const ErrorFile &errorFile) {
    if (code.find("[") == string::npos
        || code.find("return ") != string::npos) {
        //Performance optimization, filter mismatches
        return false;
    }
    
    if (auto ret = DetectorHelper::check(code, R"delimiter((\w+)\s+(\w+)\[(\w+)\])delimiter"); !ret.empty()) {
        auto prefix = StringHelper(ret.prefix()).removeSpaceAndTab();
        if (ret[1].str() != "return") {
            if (prefix.empty() || prefix == "{") {
                //check "int array_temp1[MAX];"
                m_arrays.insert({ret[2], m_helper->getIndex(ret[3], errorFile.path).first});
            }
        }
        return false;
    }


    for (const auto &item: m_arrays) {
        if (auto ret = DetectorHelper::check(code, item.first + R"delimiter(\[(\w+)\])delimiter"); !ret.empty()) {
            //check "array_temp1[INDEX];"
            auto len = m_helper->getIndex(ret[1], errorFile.path).first;
            if (len >= item.second || len < 0) {
                storeRuleError(errorFile);
                return true;
            }
        }
    }

    return false;
}

void ArrayRuleIndexOutOfBounds::resetData() {
    Rule::resetData();
    m_arrays.clear();
    m_helper->clear();
}
