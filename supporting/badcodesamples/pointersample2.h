#pragma once

int* DemoFunc()
{
    if (rand() > 1024)
    {
        int* p = new int;
        return p;
    }
    return nullptr;
}

int* DemoFunc1()
{
    if (rand() > 1024)
    {
        int* p = new int;
        return p;
    }
    return nullptr;
}
ns::Widget* findWidgetById(int id);

void playNextWidget(ns::Widget* pData, int lastWidgetId)
{
    ns::Widget* lastWidget = findWidgetById(lastWidgetId);
    assert(lastWidget != nullptr);
    if (VideoPreload::is4KVideo(lastWidget))
    {
        del4KVideoResource(lastWidget);   
        sleepMS(VIDEO_4K_DESTORY_WAIT_TIME);
        novadebug("after del 4k video resource.");
    }	
}

ns::Widget* findWidgetById(int id)
{
    ns::ScheduleWidgetContainer* pWidgetContainer = dynamic_cast<ns::ScheduleWidgetContainer*>(m_pDispatchData);
    assert(pWidgetContainer != nullptr);

    std::vector<ns::Widget>* pVec = &(pWidgetContainer->contents.widgets);
    auto itor = std::find_if(pVec->begin(), pVec->end(), [id](const ns::Widget& item) {
        return item.iId == id;
        });

    if (itor != pVec->end())
    {
        return &(*itor);
    }
    novaerror("widget with id : {} not found in the container .", id);
    return nullptr;
}

void PointerRuleReturnNullDemo()
{
    int* p = DemoFunc();
    p = DemoFunc();
    int *p1 = DemoFunc1();
    if (p == nullptr)
    {
        *p = 4;
    }
    
    if (p1 != nullptr)
    {
        
    }
    *p1 = 3;
}

void func1()
{
	if(obj != nullptr) // obj判空
	{
		obj->dosth();
	}
}

void func2()
{
    obj->dosth2();
}