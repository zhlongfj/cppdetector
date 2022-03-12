#pragma once

int sz[] = { 1,2,4 }
int SizeOfRuleFuncParameterDemo1(int32_t sz[3])
{
    auto ss = sizeof(sz);
    return ss;
}

int SizeOfRuleFuncParameterDemo2()
{
    int sz;
    auto ss = sizeof(sz);
    return ss;
}

int SizeOfRuleRepetitionDemo()
{
    int a = 0;
    int n = sizeof(sizeof(a));
}

void SizeOfRuleWithNumberDemo()
{
    int n = sizeof(9);
}
