void LoopRuleVariableModifiedDemo()
{
    for (int ii = 0; ii < 10; ++ii)
    {
        ii == 2;
        for (int ii = 0; ii < 20; ++ii)
    }
}

void LoopRuleWrongVariableDemo(int iMax)
{
    for (int i = 0; i < iMax; ++j)
    {

    }
}

void LoopRuleOutOfBoundsDemo(std::string& str, char ch)
{
    for (std::string::const_iterator iter = str.begin(); iter != str.end(); ++iter)
    {
        if (*(iter + 1) == ch)
        {
        }
    }
}