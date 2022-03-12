#pragma once
//todo: 将此内容放到acrossdynamicsample.h无法检测出来，后续解决
class OUTPUT Test
{
public:
    void f() {}
};

class OUTPUT Test2 : public Test
{
public:
    void ff() 
	{
		FF::dd();
	}
};

