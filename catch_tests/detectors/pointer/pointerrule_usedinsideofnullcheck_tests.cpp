#include "../../catch.hpp"
#include<regex>
#include "detectors/pointer/pointerrule_usedinsideofnullcheck.h"

static constexpr auto content1 = R"delimiter(
int Demo(STNullPointer* npSt)
{
	if(!npSt)
	{
		// npSt为空时解引用
		int nResult = npSt->m_node;  
		return nResult;
	}
	return 0;
}
)delimiter";

static constexpr auto content2 = R"delimiter(
int Demo(STNullPointer* npSt)
{
	if(npSt == nullptr)
	{
		// npSt为空时解引用
		int nResult = npSt->m_node;  
		return nResult;
	}
	return 0;
}
)delimiter";

static constexpr auto content3 = R"delimiter(
int Demo(STNullPointer* npSt)
{
	// if条件表达式存在逻辑漏洞，&&应该换成||
	if(npSt == nullptr && npSt->m_node)
	{
		return nResult;
	}
	return 0;
}
)delimiter";

SCENARIO("PointerRuleUsedInsideOfNULLCheck", "") {
    GIVEN("") {
        WHEN("") {
            THEN("no explicit") {
                PointerRuleUsedInsideOfNULLCheck rule;
                CHECK(rule.detect(content1, "dd"));
            }
            THEN("no explicit") {
                PointerRuleUsedInsideOfNULLCheck rule;
                CHECK(rule.detect(content2, "dd"));
            }
            THEN("no explicit") {
                PointerRuleUsedInsideOfNULLCheck rule;
                CHECK(rule.detect(content3, "dd"));
            }
        }
    }
}