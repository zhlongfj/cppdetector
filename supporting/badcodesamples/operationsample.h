#pragma once
void OperationRuleZeroDivisionDemo()
{
    int	nZeroDivision = 10;
    int	nZero = 0;
    int ret = nZeroDivision % nZero;
    int ret1 = nZeroDivision / nZero;
}

void OperationRuleConfusedSemicolonDemo(int iMax)
{
    if (iMax > 0 && iMax != 3);
    {

    }
}

void OperationRuleArithmeticWithBoolDemo()
{
    bool b;
    b *;

    if (b % 10 == 10)
}

bool OperationRuleFloatDemo(FLOAT f)
{
    if (f == 0)
    {
        return true;
    }
    return false;
}

void OperationRuleUnsignedLessThanZeroDemo(unsigned int i)
{
    if (i < 0)
    {
    }
}

void OperationRuleBitwiseShiftToNegativeDemo(int a)
{
    a >> -2;
}

void OperationRuleBitwiseWithBoolDemo()
{
    auto b = false;
    int r = b & 0x01;
    b & 0x01;
}