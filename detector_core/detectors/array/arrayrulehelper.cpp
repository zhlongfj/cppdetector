#include "arrayrulehelper.h"
#include "detectorcommon/detectorhelp.h"
#include <cctype>
#include "../../common/stringhelper.h"
#include "common/filehelp.h"


void ArrayRuleHelper::makeData(const std::string& filePath)
{
    if (m_data.empty())
    {
        m_data = FileHelp().parse(filePath);
    }
}


int ArrayRuleHelper::getIndexWithString(const string& var, const string& filePath)
{
    if (m_data.empty())
    {
        m_data = FileHelp().parse(filePath);
    }

    if (auto ret = DetectorHelper::check(m_data, var + "\\[(\\w*)\\](\\s*=\\s*\\{*\"(\\w+)\"\\}*)*"); !ret.empty())
    {
        //check "char source[10] = {"abcdefghi"};"
        //先比较实际的字符串长度
        if (!ret[3].str().empty())
        {
            return ret[3].length() + 1;
        }
        else
        {
            return stoi(ret[1]);
        }
    }

    return 0;
}

std::pair<int, std::string> ArrayRuleHelper::getIndex(const string& arrayLen, const string& filePath)
{
    if (m_data.empty())
    {
        m_data = FileHelp().parse(filePath);
    }

    if (!StringHelper(arrayLen).isDigit())
    {
        if (auto ret = DetectorHelper::check(m_data, "#define\\s+" + arrayLen + "\\s+(\\d+)"); !ret.empty())
        {
            return { stoi(ret[1]), arrayLen };
        }
        if (auto ret = DetectorHelper::check(m_data, "constexpr\\s+\\w+\\s+" + arrayLen + "\\s*=\\s*(\\d+);"); !ret.empty())
        {
            return { stoi(ret[1]), arrayLen };
        }

        vector<string> lines = StringHelper(m_data).getLines();
        int size = 0;
        for (const auto& item : lines)
        {
            if (auto ret = DetectorHelper::check(item, "\\s+" + arrayLen + "\\s*=\\s*(-*)\\s*(\\d+);"); !ret.empty())
            {
                auto sizetmp = stoi(ret[2]);
                if (size < sizetmp)
                {
                    size = sizetmp;
                }

                if (!ret[1].str().empty())
                {
                    size = -sizetmp;
                    break;
                }
            }
        }

        return { size, arrayLen };
    }
    return { stoi(arrayLen), arrayLen };
}
