#pragma once
void LogicRuleBaseValueDemo()
{
    if (1) {};
    if (0) {};
    if (true) {};
    if (false) {};
}

void LogicRuleIncorrectOperationDemo()
{
    if ((a != 1) || (a != 3)) {}
    if ((a == 1) && (a == 3)) {}
}

void LogicRuleAssignSelfDemo()
{
    int i;
    i = i;
}

void LogicRuleStringFindDemo(std::string& str, std::string& search)
{
    if (0 <= str.find(search))
    {
    }
}

void LogicRuleExpressionRepetitionDemo(int a)
{
    if (a < 3 && a < 25)
    {
        return;
    }

    if (a >= 10 && a >= 20)
    {
        return;
    }

    if (a != 10 && a == 20) {}
}