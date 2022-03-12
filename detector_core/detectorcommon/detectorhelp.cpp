//
// Created by Hualong Zhang on 2021/4/26.
//
#include <string>
#include "detectorhelp.h"
#include <iostream>
#include "common/stringhelper.h"

smatch DetectorHelper::check(const string& content, const string& regValue) {
    regex reg(regValue);
    smatch m;
    try {
        regex_search(content, m, reg);
    }
    catch (std::regex_error error) {
        std::cout << error.what();
    }
    return m;
}

smatch DetectorHelper::checkExportClass(const string& content) {
    //check "class OUTPUT Test" or "class OUTPUT Test2 : public Test" or "class OUTPUT Test2 : private Test" or "class OUTPUT Test2 : protected Test"
    if (content.find("class ") == string::npos
        && content.find("struct ") == string::npos) {
        //Performance optimization, filter mismatches
        return smatch();
    }
    return check(content, "\\s*(class|struct)\\s+\\w+\\s+(\\w+)(\\s*:\\s*(public|protected|private)*\\s*(\\w*))*");
}

std::smatch DetectorHelper::checkFor(const string& code) {
    if (!StringHelper(code).findCode("for")) {
        return smatch();
    }
    return DetectorHelper::check(code,
        R"delimiter(for\s*\((.+)\s*=\s*.+;\s*(\w+)\s*[<>!]=*\s*.+;\s*(\+\+|--)*(\w+)(\+\+|--)*)delimiter");
}

std::smatch DetectorHelper::checkFor1(const string& code) {
    if (!StringHelper(code).findCode("for")) {
        return smatch();
    }
    return DetectorHelper::check(code,
        R"delimiter(for\s*\((.+)=\s*.+;\s*(\w+)\s*([<>!]=*)\s*(.+);\s*(.+)\))delimiter");
}

std::smatch DetectorHelper::checkInBracket(const string& code, const string& prefix) {
    if (code.find(prefix) == string::npos) {
        return smatch();
    }
    return DetectorHelper::check(code, prefix + "\\s*\\(\\s*(.+)\\s*\\)\\s*");
}

std::smatch DetectorHelper::checkIf(const string& code) {
    return checkInBracket(code, "if");
}

size_t DetectorHelper::getIndexOfRightBrace(const string& code) {
    auto index = code.rfind("}");
    if (index == string::npos) {
        return string::npos;
    }

    auto index1 = code.find("\"");
    if (index1 != string::npos
        && index1 > index) {
        return string::npos;
    }

    return index;
}

std::smatch DetectorHelper::checkNew(const string& code) {
    return DetectorHelper::check(code, "(\\w+)\\s*=\\s*new\\s+");
}

std::smatch DetectorHelper::checkConstructedObject(const string& code) {
    //m_pTimer.reset(new QTimer);
    if (code.find("=") == string::npos
        && code.find("reset") == string::npos) {
        return smatch();
    }
    return DetectorHelper::check(code, R"delimiter((\w+)((\s*=\s*\w+)|(\.reset\(\w+)))delimiter");
}

std::smatch DetectorHelper::checkTernaryOperator(const string& code) {
    if (code.find("?") == string::npos
        || code.find(":") == string::npos)
    {
        return smatch();
    }
    return DetectorHelper::check(code, "(.+)\\?(.+):(.+)");
}

string DetectorHelper::checkClassDefinition(const string& code) {
    if (code.find("class") == string::npos
        && code.find("struct") == string::npos) {
        return "";
    }

    auto codeTmp = code;
    auto index = code.find(" final");
    if (index != string::npos) {
        codeTmp = code.substr(0, index);
    }
    auto ret = DetectorHelper::check(codeTmp, "^\\s*(struct|class)(\\s\\w*)*\\s+(\\w+)");
    if (ret.empty()) {
        return "";
    }

    return ret[3];
}

string DetectorHelper::checkDestructor(const string& code) {
    auto index = code.find("~");
    if (index == string::npos
        || code.find("\"") != string::npos) {
        return "";
    }

    auto index1 = code.find("()");
    if (index1 == string::npos) {
        return "";
    }

    return code.substr(index + 1, index1 - index);
}

bool DetectorHelper::isFunctionDefinition(const string& content) {
    auto ret = getNameOfFunctionDefinition(content);
    return !ret.empty();
}

string DetectorHelper::getNameOfFunctionDefinition(const string& content) {
    if (content.find("(") == string::npos) {
        //Performance optimization, filter mismatches
        return "";
    }

    StringHelper helper(content);
    if (helper.findCode("else if"))
    {
        //else if(a == b)
        return "";
    }

    auto contentTmp = helper.removeSpaceAndTab();
    auto index = contentTmp.rfind(";");
    if (index != string::npos && index == contentTmp.size() - 1) {
        return "";
    }

    if (auto ret = DetectorHelper::check(content, R"delimiter(((\w+)::)*~*(\w+)\()delimiter"); !ret.empty()) {
        auto domain = ret[2].str();
        auto funcName = ret[3].str();
        if (domain == funcName) {
            return funcName;
        }

        auto suffix = ret.suffix().str();
        if (suffix.find(" override") != string::npos
            || suffix.find(" const") != string::npos)
        {
            return funcName;
        }

        auto prefix = ret.prefix().str();
        if (!DetectorHelper::check(prefix, "\\w+\\s*$").empty()
            || !DetectorHelper::check(prefix, R"delimiter(\w+\s*<.+>(\*|\&)*\s*$)delimiter").empty()
            || !DetectorHelper::check(prefix, R"delimiter(\w+\s*(\*|\&)*\s*$)delimiter").empty()) {
            if (suffix.find("\"") != string::npos) {
                //_bstr_t(L"ROOT\\CIMV2"), 
                return "";
            }

            auto suffixWithoutSpace = StringHelper(suffix).removeSpaceAndTab();
            //PUB* pub)    PUB *pub),    PUB * pub),
            //PUB&* pub)   PUB &*pub),   PUB &* pub)
            //PUB& pub)    PUB &pub),    PUB & pub)
            //PUB pub)
            //add '>*' for void Demo(std::vector<int>& ivec)
            bool parameterOfFunc = !DetectorHelper::check(suffix, R"delimiter(\w+>*&*\**\s+)delimiter").empty();
            if (suffixWithoutSpace.empty()
                || suffixWithoutSpace == ")"
                || suffixWithoutSpace == "){"
                || parameterOfFunc) {
                return funcName;
            }
            //ddf(33)
            //int(pAdapter->Address[0]),
            return "";
        }
    }

    if (auto ret = DetectorHelper::check(content, "operator.+\\(.*\\)"); !ret.empty()) {
        auto suffix = ret.suffix().str();
        if (!suffix.empty() && suffix[suffix.size() - 1] != ';') {
            return "operator";
        }
    }
    return "";
}

FuncInfoOfCalled DetectorHelper::getInfoOfFunctionCalled(const string& content) {
    if (content.find("(") == string::npos) {
        return { "", "" };
    }

    auto ret = DetectorHelper::check(content, R"delimiter((\w+)\(.*\);$)delimiter");
    if (ret.empty()) {
        return { "", "" };
    }

    auto ret1 = DetectorHelper::check(ret.prefix().str(), R"delimiter((\w+)\s*=)delimiter");
    if (ret1.empty())
    {
        ret1 = DetectorHelper::check(ret.suffix().str(), R"delimiter((\w+)\s*=)delimiter");
        if (ret1.empty())
        {
            return { ret[1].str(), "" };
        }
    }
    return { ret[1].str(), ret1[1].str() };
}

string DetectorHelper::getReturnTypeOfFunctionDefinition(const string& content) {
    if (content.find(")") == string::npos)
    {
        //Performance optimization, filter mismatches
        return "";
    }

    if (auto ret = DetectorHelper::check(content, "(\\w+)\\s+(\\w+::)*\\w+\\(.*\\)"); !ret.empty()) {
        if (ret.prefix().str().find("\"") == string::npos) {
            return ret[1];
        }
    }
    return "";
}

std::pair<std::string, std::string>
DetectorHelper::getValueFromOperator(const string& content, const string& operationalCharacter) {
    if (content.find(operationalCharacter) == string::npos) {
        //Performance optimization, filter mismatches
        return { "", "" };
    }
    auto ret = DetectorHelper::check(content, "(\\w+)\\s*" + operationalCharacter + "\\s*(.+)");
    if (ret.empty()) {
        return { "", "" };
    }

    return { ret[1], ret[2] };
}