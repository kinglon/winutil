#include "EventDispatcher.h"
#include <assert.h>
using namespace std;

CEventDispatcher::CEventDispatcher()
{
}

CEventDispatcher::~CEventDispatcher()
{
}

CEventDispatcher* CEventDispatcher::GetInstance()
{
    static CEventDispatcher* pInstance = new CEventDispatcher();
    return pInstance;
}

void CEventDispatcher::DispatchEvent(int nEventId, const std::string& strEventData)
{
    auto it = m_mapEventId2Handlers.find(nEventId);
    if (it != m_mapEventId2Handlers.end())
    {
        //����һ�ݴ������б������ڱ������ô�����ʱ���������ڲ�����ע��/��ע�ᣬ���µ�����ʧЧ����
        set<IOnHandleEvent*> setHandlers = it->second;
        for (auto itHandlers = setHandlers.begin(); itHandlers != setHandlers.end(); ++itHandlers)  //�˴��������б��ǿ������Ƿ�
        {
            (*itHandlers)->OnHandleEvent(nEventId, strEventData);
        }
    }
}

void CEventDispatcher::RegisterHandler(int nEventId, IOnHandleEvent* pHandler)
{
    assert(pHandler);
    auto it = m_mapEventId2Handlers.find(nEventId);
    if (it == m_mapEventId2Handlers.end())
    {
        m_mapEventId2Handlers[nEventId] = set < IOnHandleEvent* > {pHandler};
    }
    else
    {
        it->second.insert(pHandler);
    }
}

void CEventDispatcher::UnRegisterHandler(int nEventId, IOnHandleEvent* pHandler)
{
    assert(pHandler);
    auto it = m_mapEventId2Handlers.find(nEventId);
    if (it != m_mapEventId2Handlers.end())
    {
        it->second.erase(pHandler);
    }
}

void CEventDispatcher::UnRegisterHandler(IOnHandleEvent* pHandler)
{
    for (auto it = m_mapEventId2Handlers.begin(); it != m_mapEventId2Handlers.end(); ++it)
    {
        it->second.erase(pHandler);
    }
}