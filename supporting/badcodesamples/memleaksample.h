#pragma once

void MemLeakRuleNewWithOutDeleteDemo()
{
    char* p = new char;
    p = nullptr;
}

void MemLeakRuleReallocDemo()
{
    char* buf = (char*)malloc(10);
    char* p = buf[1];
    buf = (char*)realloc(buf, 100);
    *p = 'a';
    free(buf);
}

void MemLeakRuleFileHandleDemo1()
{
    FILE* pFile = fopen("c:\\test.txt", "w+");
}

void MemLeakRuleFileHandleDemo2()
{
    FILE* pFile = fopen("c:\\test.txt", "w+");
    fclose(pFile);
}

"~dd";
class Derived : public Base
{
public: 
    ~Derived()
	{
		(void)11;
	}
};