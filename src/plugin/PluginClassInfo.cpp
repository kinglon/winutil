#include "PluginClassInfo.h"
#include <assert.h>

CPluginClassInfo* CPluginClassInfo::m_pFirst = nullptr;

CPluginClassInfo::CPluginClassInfo(const std::string& strId, FnCreatePluginInstance pCreatorFun)
{ 
    assert(!strId.empty());
    assert(pCreatorFun);
    m_strId = strId;
    m_pCreatorFun = pCreatorFun;
    if (m_pFirst == nullptr)
    {
        m_pFirst = this;
    }
    else
    {
        this->m_pNext = m_pFirst->m_pNext;
        m_pFirst->m_pNext = this;
    }
}

CPluginClassInfo::~CPluginClassInfo()
{
}