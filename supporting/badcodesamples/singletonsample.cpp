#include "singletonsample.h"

//tpdo: 放到头文件无法检测出来
Test* getInstance()
{
    if (NULL == m_tt)
    {
        m_tt = new Test();
    }
    return m_tt;
}