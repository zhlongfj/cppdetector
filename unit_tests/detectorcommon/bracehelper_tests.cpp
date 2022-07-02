#include "../doctest.h"
#include "../../detector_core/detectorcommon/bracehelper.h"

static constexpr auto code = R"delimiter(
bool BraceHelper::leftBraceAfterRightParenthesis(const string& codeWithoutSpace)
{
    string braceAfterRightParenthesis = "){";
    if (codeWithoutSpace.size() < 2)
    {
        return false;
    }

    auto index = codeWithoutSpace.rfind(braceAfterRightParenthesis);
    return index != string::npos;
}
)delimiter";

SCENARIO("BraceHelper") {
    GIVEN("") {
        WHEN("") {
            THEN("The function declaration and implementation are on the same line") {
                BraceHelper braceHelper;
                auto count = braceHelper.calculateCountOfOpenBrace("bool findLeftBrace() { return m_findBrace; }", 1);
                CHECK(count == 0);
                CHECK(braceHelper.findOpenBrace());
            }
            THEN("The function implementation contains double quotes") {
                BraceHelper braceHelper;
                int count = 0;
                StringHelper stringHelper(code);
                auto lines = stringHelper.getLines();
                for (const auto item : lines)
                {
                    count = braceHelper.calculateCountOfOpenBrace(item, 1);
                }
                CHECK(count == 0);
                CHECK(braceHelper.findOpenBrace());
            }
            THEN("There are more close braces than open braces") {
                BraceHelper braceHelper;
                auto count = braceHelper.calculateCountOfOpenBrace("bool findLeftBrace() { return m_findBrace; }", 1);
                CHECK(braceHelper.findOpenBrace());
            }
        }
    }
}