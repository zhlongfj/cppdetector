void Demo(C* obj)
{
	if(obj != NULL)
	{
		obj->dosth();
	}

	obj->dosth2();
}

void Demo1(C* obj1)
{
	if(obj1 != NULL) {
		obj1->dosth();
	}

	obj1->dosth2();
}

void Demo2(C* obj1)
{
	if(obj1 == NULL) {
		obj1->dosth();
	}
}

void Demo3(C* obj1)
{
	obj1->dosth();
}

void func4(int* p)
{
	p = func_ret_null();
	if(p == NULL)
		return;

	*p = 42;
}

void func_error(int* p)
{
	p = func_ret_null();
	*p = 42;
}

int Demo(int i)
{
	STNullPointer* npSt = nullptr;
	STNullPointer* npSt1;
	STNullPointer* npSt2;
	npSt2 = dd;
	if(i == 42)
		return;

	npSt->m_node = 42;
	npSt1->m_node = 42;
	npSt2->m_node = 42;
}

int Demo1(int i)
{
	npSt1->m_node = 42;
}

int Demo(STNullPointer* npSt)
{
	delete npSt;
	npSt->m_node;
	return 0;
}

int Demo(STNullPointer* npSt)
{
	if(npSt == nullptr && npSt->m_node)
	{
		return nResult;
	}
	
	if(npSt == nullptr &&
		npSt->m_node)
	{
		return nResult;
	}
	
	if(npSt == nullptr
		&& npSt->m_node)
	{
		return nResult;
	}
	return 0;
}

void Demo(std::vector<int>& ivec)
{
	std::vector<int>::iterator iter;
	for(iter = ivec.begin();iter!=ivec.end();iter++)
	{
		
		
	}
	cout<<*iter;
}

char* Demo()
{
    char sz[] = "hello TspyCode!";
    return sz;
}

int& Demo()
{
    int n = 0;
    return n;
}