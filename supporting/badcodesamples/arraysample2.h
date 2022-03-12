void Demo(int j)
{
    int a[10] = { 0 };

    int i = 9;
    if (j > 5)
    {
        i = -1;
    }

    a[i] = a[i] + 1;
}


char szStrTime[5];
char source[10] = {"abcde"};

snprintf(szStrTime, 5, "%s", source);
strcpy(szStrTime, source);
strncpy(szStrTime, "12345", 5);