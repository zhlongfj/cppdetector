#include "../catch.hpp"
#include "../../detector_core/detectorcommon/ifdefinition.h"

SCENARIO("IfDefinition", "") {
    GIVEN("") {
        WHEN("") {
            THEN("scenario1") {
                IfDefinition definition;
                CHECK(definition.inIfDefinition("if((npSt == nullptr)"));
                CHECK(!definition.isEnd());
                CHECK(definition.condition() == "(npSt==nullptr)");
                CHECK(definition.inIfDefinition(" && (npSt->m_node))"));
                CHECK(definition.isEnd());
                CHECK(definition.condition() == "(npSt==nullptr)&&(npSt->m_node)");
                auto conditions = definition.getConditionContexts();
                CHECK(conditions[0].conditionExpresss == "(npSt==nullptr)");
                CHECK(conditions[0].logicalOperatorToNext == "&&");
                CHECK(conditions[0].operands.first == "npSt");
                CHECK(conditions[0].operands.second == "nullptr");

                CHECK(conditions[1].conditionExpresss == "(npSt->m_node)");
                CHECK(conditions[1].logicalOperatorToNext == "");
                CHECK(conditions[1].operands.first == "npSt->m_node");
                CHECK(conditions[1].operands.second.empty());

            }
            THEN("scenario2") {
                IfDefinition definition;
                CHECK(definition.inIfDefinition("if(npSt == nullptr && npSt->m_node)"));
                CHECK(definition.isEnd());
                CHECK(definition.condition() == "npSt==nullptr&&npSt->m_node");

                auto conditions = definition.getConditionContexts();
                CHECK(conditions[0].conditionExpresss == "npSt==nullptr");
                CHECK(conditions[0].operatorName == "==");
                CHECK(conditions[0].logicalOperatorToNext == "&&");
                CHECK(conditions[0].operands.first == "npSt");
                CHECK(conditions[0].operands.second == "nullptr");

                CHECK(conditions[1].conditionExpresss == "npSt->m_node");
                CHECK(conditions[1].operatorName.empty());
                CHECK(conditions[1].logicalOperatorToNext.empty());
                CHECK(conditions[1].operands.first == "npSt->m_node");
                CHECK(conditions[1].operands.second.empty());
            }
            THEN("scenario3") {
                IfDefinition definition;
                CHECK(definition.inIfDefinition("if(npSt == nullptr "));
                CHECK(!definition.isEnd());
                CHECK(definition.condition() == "npSt==nullptr");
                CHECK(definition.inIfDefinition("    && npSt->m_node"));
                CHECK(!definition.isEnd());
                CHECK(definition.condition() == "npSt==nullptr&&npSt->m_node");
                CHECK(definition.inIfDefinition("    || npSt->m_node1 )"));
                CHECK(definition.isEnd());
                CHECK(definition.condition() == "npSt==nullptr&&npSt->m_node||npSt->m_node1");

                auto conditions = definition.getConditionContexts();
                CHECK(conditions[0].conditionExpresss == "npSt==nullptr");
                CHECK(conditions[0].operatorName == "==");
                CHECK(conditions[0].logicalOperatorToNext == "&&");
                CHECK(conditions[0].operands.first == "npSt");
                CHECK(conditions[0].operands.second == "nullptr");

                CHECK(conditions[1].conditionExpresss == "npSt->m_node");
                CHECK(conditions[1].operatorName.empty());
                CHECK(conditions[1].logicalOperatorToNext == "||");
                CHECK(conditions[1].operands.first == "npSt->m_node");
                CHECK(conditions[1].operands.second.empty());

                CHECK(conditions[2].conditionExpresss == "npSt->m_node1");
                CHECK(conditions[1].operatorName.empty());
                CHECK(conditions[2].logicalOperatorToNext == "");
                CHECK(conditions[2].operands.first == "npSt->m_node1");
                CHECK(conditions[2].operands.second.empty());

                CHECK(!definition.inIfDefinition("    && npSt->m_node"));
                CHECK(!definition.isEnd());
                CHECK(definition.condition().empty());
            }
            THEN("scenario4") {
                IfDefinition definition;
                auto code = R"delimiter(if (auto ret = DetectorHelper::check(code, "\\w+\\s+(\\w+)\\[(\\w+)\\]"); !ret.empty()))delimiter";
                CHECK(definition.inIfDefinition(code));
                CHECK(definition.condition() == "!ret.empty()");

                CHECK(definition.inIfDefinition("if (iCount = 0)"));
                CHECK(definition.condition() == "iCount=0");
            }
            THEN("scenario5") {
                //未测试
                //if中间有\"
                //if 中间有括号，比如：if ((a == 1 || b == 2) && c == 3) 可以通过先识别出来括号的内容
            }
        }
    }
}