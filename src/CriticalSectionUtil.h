#pragma once

/***
临界区对象，构造函数自动进入临界区，析构函数自动释放临界区，析构之前可手动调Leave提前离开临界区
*/
class CCriticalSectionUtil
{
public:
    CCriticalSectionUtil(CRITICAL_SECTION* pCS);
    ~CCriticalSectionUtil();

public:
    /**
    @name 离开临界区
    */
    void Leave();

private:
    CRITICAL_SECTION* m_pCS = nullptr;
    bool m_bAlreadyLeave = false;
};