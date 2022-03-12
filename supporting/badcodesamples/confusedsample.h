#pragma once

void ConfusedRuleSemicolonDemo(int iMax)
{
    if (iMax > 0 && iMax != 3);
    {

    }
}

int ConfusedRuleBreakDemo(int iMax)
{
    int iCount = 0;
	while (iCount < iMax)
    {
		break;
        iCount++;
    }
    return iCount;
}

void ConfusedRulePriorityDemo(int iMax)
{
    int iTemp = 10 << iMax + 3;
}

void ConfusedRulePriorityWithAssignmentAndCompareDemo()
{
    int x = 3;
    if (x = 4 > 3)
    {
    }
}

void ConfusedRuleCaseWithoutBreakDemo(int a)
{
    switch (a) {
    case 1:
        break;
    case 2:
        int i = 0;
    default:
        break;
    }
}

void ConfusedRuleStatementOutsideOfCaseDemo(int b)
{
    int c = 0;
    switch (b)
    {
        c = 3;// case之前不应该有代码
    case 2:
        //
        c = 2;
        break;
    default:
        break;
    }
}

void ConfusedRuleStatementOutsideOfCaseDemo(int b)
{
    int c = 0;
    switch (b)
    {
    case 2:
        c = 2;
        break;
    }
    int a = 6;
}

int ConfusedRuleConditionRepeatDemo(int a, int b)
{
    // if和elseif的条件是一样的
    if (a == b)
    {
        return 1;
    }
    else if (a == b)
    {
        return 2;
    }

    return 0;
}

void ConfusedRuleAssignmentInAssertDemo()
{
    int iCount = 2;
    if (iCount = 0)
    {
        iCount = 2;
    }

    int i = 0;
    assert(i = 5);
    assert(i == 5);
}

bool ConfusedRuleReturnBoolRetFunc()
{
    if (rand() > 10)
    {
        return 10;
    }
    return 1;
}

void func111()
{
	for (int i = 0; i < 10; i++)
	{
		switch (vecParagraph[i].horizontalAlignment)
        {
        case HAlignment::HCENTER:
        {
            qstrAlign = " align=\"CENTER\">";
        }
        break;
        case HAlignment::HLEFT:
        {
            qstrAlign = " align=\"LEFT\">";
        }
        break;
        case HAlignment::HRIGHT:
        {
            qstrAlign = " align=\"RIGHT\">";
        }
        break;
        }
		break;
	}