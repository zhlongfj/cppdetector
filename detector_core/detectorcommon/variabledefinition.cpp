#include "variabledefinition.h"

bool VariableDefinition::isVariableDefinition(const string &content) {
    resetData();
    auto helper = StringHelper(content);
    helper.trim();
    if (helper.content().find("using ") == 0
        || helper.content().find("namespace ") == 0
        || helper.content().find("return ") == 0
        || helper.content().find("extern ") == 0
        || helper.content().find("class ") == 0
        || helper.content().find("struct ") == 0
        || helper.content().find("enum ") == 0
        || helper.content().find("typedef ") == 0
        || helper.content().find(" operator") != string::npos) {
        return false;
    }

    m_isStatic = helper.remove("static ");
    m_isConstexpr = helper.remove("constexpr ");
    m_isConst = helper.remove("const ");
    m_isRvalueReference = helper.content().find("&&") != string::npos;
    m_isReference = helper.content().find("&") != string::npos;
    m_isPointToPoint = checkPoint(helper.content(), "**");
    m_isPoint = checkPoint(helper.content(), "*");

    auto codeTmp = separateOutVariableDeclaration(helper.content());
    if (codeTmp.empty()) {
        return false;
    }

    if (codeTmp.rfind(";") == string::npos) {
        codeTmp += ';';
    }

    auto ret = DetectorHelper::check(codeTmp, R"delimiter((\s+|(\s*[&*]+\s*))((\w+::)*\w+)(\[\w+\])*;$)delimiter");
    if (ret.empty() && !ret.prefix().matched) {
        return false;
    }

    if (ret.prefix().matched
        && ret.prefix().str().back() == ':') {
        return false;
    }
    auto type = ret.prefix().str();
    if (!validType(type)) {
        return false;
    }
    m_type = type;
    m_name = ret[3];
    return true;
}

std::string VariableDefinition::separateOutVariableDeclaration(const string &code) {
    if (code.find("{") == string::npos
        && code.find("=") == string::npos
        && code.find("(") == string::npos)
    {
        //Performance optimization, filter mismatches
        return code;
    }
    auto ret = DetectorHelper::check(code, R"delimiter(\s*((\{.*)|(=.*)|(\(.*)))delimiter");
    if (ret.empty()) {
        return code;
    }

    m_isInitialized = true;
    if (!ret.prefix().matched) {
        return "";
    }

    auto targetContent = ret[1].str();
    if (targetContent[0] == '(') {
        if (auto ret1 = DetectorHelper::check(targetContent,
                                              R"delimiter(^\((\s*\))|(((\w+::)*\w+(\s+|(\s*[&*<]+\s*))\w+)))delimiter"); !ret1.empty()) {
            //void func()
            //void func(int i)
            //QString mapValToString(QMap<QString, QVariant> &conditionMap);
            return "";
        }
    }

    return ret.prefix().str();
}

void VariableDefinition::resetData() {
    m_isStatic = false;
    m_isConst = false;
    m_isConstexpr = false;
    m_isPoint = false;
    m_isPointToPoint = false;
    m_isReference = false;
    m_isRvalueReference = false;
    m_isInitialized = false;
    m_type.clear();
    m_name.clear();
    m_content.clear();
}

bool VariableDefinition::checkPoint(const string &content, const string &pointMark) {
    if (auto index = content.find(pointMark); index != string::npos) {
        auto index1 = content.find(">", index);
        if (index1 == string::npos
            || index1 != index + pointMark.size()) {
            return true;
        }
    }
    return false;
}

bool VariableDefinition::validType(const string &code) {
    //std::cout << "ss" << width << "*" << height << endl;
    auto iterOfLeftAngle = code.find("<");
    auto iterOfRightAngle = code.find(">");
    if (iterOfLeftAngle != string::npos && iterOfRightAngle == string::npos
        || iterOfLeftAngle == string::npos && iterOfRightAngle != string::npos) {
        return false;
    }

    return true;
}
