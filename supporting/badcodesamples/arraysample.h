#pragma once

#define MAX 100
#define INDEX 200
constexpr int MAX1 = 100;
constexpr int INDEX1 = 200;
void indexoutofboundsDemo()
{
    int array_temp[100];
    array_temp[200];

    int array_temp1[MAX];
    array_temp1[INDEX];

    int array_temp2[MAX1];
    array_temp2[INDEX1];
}

void indexoutofboundsDemo(int b)
{
    int max = 5;
    int a[10];
    if (b > 0)
    {
        max = 10;
    }

    a[max] = max;
}

void indexusedbeforedcheckDemo(int index)
{
    char buf[10] = { 0 };
    if (buf[index] > 0 && index <= INDEX)
        return;
    if (buf[index] > 0
        && index < INDEX)
        return;
    if (buf[index] > 0 &&
        index < INDEX)
        return;
}

void indexcheckdefectivelyDemo1(int index)
{
    int buf[10];
    if (index < 0 || index > 10)
    {
        return;
    }
    buf[index] = 3;
}

void indexcheckdefectivelyDemo2(int index)
{
    int buf[MAX];
    if (index < 0 || index > MAX)
    {
        return;
    }
    buf[index] = 3;
}

void BufferOverflowDemo()
{
    char sz[2];
    strcpy(sz, "123");
    char sz[MAX1];
    strncpy(sz, "123", 3);
}

class ArrayRuleIndexOutOfBoundsFromFuncDemo()
{
    char buf[INDEX1];
    int length = getLenFromBuf(INDEX1);
    buf[length] = 'Q';
}

void ArrayRuleIndexOutOfBoundsInLoopDemo()
{
    char buf[INDEX];
    for (unsigned int i = 0; i <= INDEX; ++i)
    {
        buf[i] = 'a';
    }

    for (unsigned int i = 0; i < INDEX; ++i)
    {
        buf[i] = 'a';
    }
}

void ArrayRuleMemsetDemo()
{
    char* p = new char[100];
    memset(p, 100, 0);
    delete[] p;
}