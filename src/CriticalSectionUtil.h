#pragma once

/***
�ٽ������󣬹��캯���Զ������ٽ��������������Զ��ͷ��ٽ���������֮ǰ���ֶ���Leave��ǰ�뿪�ٽ���
*/
class CCriticalSectionUtil
{
public:
    CCriticalSectionUtil(CRITICAL_SECTION* pCS);
    ~CCriticalSectionUtil();

public:
    /**
    @name �뿪�ٽ���
    */
    void Leave();

private:
    CRITICAL_SECTION* m_pCS = nullptr;
    bool m_bAlreadyLeave = false;
};