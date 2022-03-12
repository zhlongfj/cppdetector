#include "codeconversion.h"
#include <codecvt>
#include <locale>
#include <vector>

std::string CodeConversion::gb2312_to_utf8(std::string const& strGb2312)
{
    std::vector<wchar_t> buff(strGb2312.size());
#ifdef _MSC_VER
    std::locale loc("zh-CN");
#else
    std::locale loc("zh_CN.GB18030");
#endif
    wchar_t* pwszNext = nullptr;
    const char* pszNext = nullptr;
    mbstate_t state = {};
    int res = std::use_facet<std::codecvt<wchar_t, char, mbstate_t> >
        (loc).in(state,
            strGb2312.data(), strGb2312.data() + strGb2312.size(), pszNext,
            buff.data(), buff.data() + buff.size(), pwszNext);

    if (std::codecvt_base::ok == res)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> cutf8;
        return cutf8.to_bytes(std::wstring(buff.data(), pwszNext));
    }

    return "";
}

std::string CodeConversion::utf8_to_gb2312(std::string const& strUtf8)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> cutf8;
    std::wstring wTemp = cutf8.from_bytes(strUtf8);
#ifdef _MSC_VER
    std::locale loc("zh-CN");
#else
    std::locale loc("zh_CN.GB18030");
#endif
    const wchar_t* pwszNext = nullptr;
    char* pszNext = nullptr;
    mbstate_t state = {};

    std::vector<char> buff(wTemp.size() * 2);
    int res = std::use_facet<std::codecvt<wchar_t, char, mbstate_t> >
        (loc).out(state,
            wTemp.data(), wTemp.data() + wTemp.size(), pwszNext,
            buff.data(), buff.data() + buff.size(), pszNext);

    if (std::codecvt_base::ok == res)
    {
        return std::string(buff.data(), pszNext);
    }
    return "";
}

Encode CodeConversion::checkCodeFormat(const uint8_t* data, size_t size)
{
    bool bAnsi = true;

    uint8_t ch = 0x00;

    int32_t nBytes = 0;

    for (auto i = 0; i < size; i++)

    {

        ch = *(data + i);

        if ((ch & 0x80) != 0x00)

        {

            bAnsi = false;

        }

        if (nBytes == 0)

        {

            if (ch >= 0x80)

            {

                if (ch >= 0xFC && ch <= 0xFD)

                {

                    nBytes = 6;

                }

                else if (ch >= 0xF8)

                {

                    nBytes = 5;

                }

                else if (ch >= 0xF0)

                {

                    nBytes = 4;

                }

                else if (ch >= 0xE0)

                {

                    nBytes = 3;

                }

                else if (ch >= 0xC0)

                {

                    nBytes = 2;

                }

                else

                {

                    return Encode::ANSI;

                }

                nBytes--;

            }

        }

        else

        {

            if ((ch & 0xC0) != 0x80)

            {

                return Encode::ANSI;

            }

            nBytes--;

        }

    }

    if (nBytes > 0 || bAnsi)

    {

        return Encode::ANSI;

    }

    return Encode::UTF8;
}
