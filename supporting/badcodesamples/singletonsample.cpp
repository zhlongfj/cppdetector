#include "singletonsample.h"

//tpdo: �ŵ�ͷ�ļ��޷�������
Test* getInstance()
{
    if (NULL == m_tt)
    {
        m_tt = new Test();
    }
    return m_tt;
}