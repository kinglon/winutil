#include "stdafx.h"
#include "CriticalSectionUtil.h"

CCriticalSectionUtil::CCriticalSectionUtil(CRITICAL_SECTION* pCS)
{
    m_pCS = pCS;
    if (m_pCS)
    {
        EnterCriticalSection(m_pCS);
    }    
}

CCriticalSectionUtil::~CCriticalSectionUtil()
{
    if (!m_bAlreadyLeave)
    {
        if (m_pCS)
        {
            LeaveCriticalSection(m_pCS);
        }        
    }    
}

void CCriticalSectionUtil::Leave()
{
    if (!m_bAlreadyLeave)
    {
        m_bAlreadyLeave = true;
        if (m_pCS)
        {
            LeaveCriticalSection(m_pCS);
        }
    }
}