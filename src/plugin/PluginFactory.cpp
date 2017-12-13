#include "PluginFactory.h"
#include "PluginClassInfo.h"

CPluginFactory::CPluginFactory()
{
}

CPluginFactory::~CPluginFactory()
{
}

IPlugin* CPluginFactory::CreatePlugin(const std::string& strId)
{
    CPluginClassInfo* pClassInfo = CPluginClassInfo::m_pFirst;
    while (pClassInfo)
    {
        if (strId == pClassInfo->m_strId && pClassInfo->m_pCreatorFun)
        {
            return pClassInfo->m_pCreatorFun(strId);
        }

        pClassInfo = pClassInfo->m_pNext;
    }

    return nullptr;
}

void CPluginFactory::DeletePlugin(IPlugin* pPlugin)
{
    if (pPlugin)
    {
        delete pPlugin;
    }
}