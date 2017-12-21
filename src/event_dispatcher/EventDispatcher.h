#pragma once
#include <string>
#include <map>
#include <set>
#include <assert.h>

/**
�����¼�����ӿ�
*/
class IOnHandleEvent
{
public:
    /**
    @name �����¼��ӿ�
    @param nEventId �¼�ID
    @param strEventData Я���¼���������
    */
    virtual void OnHandleEvent(int nEventId, const std::string& strEventData) = 0;
};

/**
�����¼��������ģ����
*/
template <class T>
class COnHandleEventDelegate : public IOnHandleEvent
{
public: //implement IOnHandleEvent
    virtual void OnHandleEvent(int nEventId, const std::string& strEventData) override
    {
        if (m_pObject && m_pOnHandleEventFunction)
        {
            (m_pObject->*m_pOnHandleEventFunction)(nEventId, strEventData);
        }
    }

public:
    T* m_pObject = nullptr;
    void (T::*m_pOnHandleEventFunction)(int nEventId, const std::string& strEventData) = nullptr;
};

/**
�����¼�������ע��/��ע�ᡢ�¼��ַ�
*/
class CEventDispatcher
{
private:
    CEventDispatcher();
    ~CEventDispatcher();

public:
    /**
    @name ��ȡ��������
    */
    static CEventDispatcher* GetInstance();

    /**
    @name ����ַ��¼�
    @param nEventId �¼�ID
    @param strEventData �¼�Я������
    */
    void DispatchEvent(int nEventId, const std::string& strEventData);

    /**
    @name ע���¼�������
    @param nEventId �¼�ID
    @param pHandler ������
    */
    void RegisterHandler(int nEventId, IOnHandleEvent* pHandler);
    
    /**
    @name ��ע���¼�������
    @param nEventId �¼�ID
    @param pHandler ������
    */
    void UnRegisterHandler(int nEventId, IOnHandleEvent* pHandler);

    /**
    @name ��ע��ָ���������������¼�
    @param pHandler ������
    */
    void UnRegisterHandler(IOnHandleEvent* pHandler);

    /**
    @name ע���¼�������
    @param nEventId �¼�ID
    @param pObject ��������Ա������������
    @param pOnHandleEventFunction ��Ա������ַ
    */
    template <class T> void RegisterHandler(int nEventId, T* pObject, void (T::*pOnHandleEventFunction)(int, const std::string&));

    /**
    @name ��ע���¼�������
    @param nEventId �¼�ID
    @param pObject ��������Ա������������
    */
    template <class T> void UnRegisterHandler(int nEventId, T* pObject);

    /**
    @name ��ע��ָ����������д�����
    @param pObject ��������Ա������������
    */
    template <class T> void UnRegisterHandler(T* pObject);

private:
    std::map<int, std::set<IOnHandleEvent*>> m_mapEventId2Handlers;
};

template <class T> void CEventDispatcher::RegisterHandler(int nEventId, T* pObject, void (T::*pOnHandleEventFunction)(int, const std::string&))
{
    assert(pObject && pOnHandleEventFunction);
    if (pObject == nullptr || pOnHandleEventFunction == nullptr)
    {
        return;
    }    
    
    auto it = m_mapEventId2Handlers.find(nEventId);
    if (it == m_mapEventId2Handlers.end())
    {
        COnHandleEventDelegate<T>* pHandler = new COnHandleEventDelegate<T>();
        pHandler->m_pObject = pObject;
        pHandler->m_pOnHandleEventFunction = pOnHandleEventFunction;
        m_mapEventId2Handlers[nEventId] = std::set < IOnHandleEvent* > {pHandler};
    }
    else
    {       
        bool bAlreadyRegister = false;
        for (auto itHandle = it->second.begin(); itHandle != it->second.end(); ++itHandle)
        {
            if (((COnHandleEventDelegate<T>*)*itHandle)->m_pObject == pObject)
            {
                assert(false);  //���ע��
                bAlreadyRegister = true;
                break;
            }
        }
        
        if (!bAlreadyRegister)
        {
            COnHandleEventDelegate<T>* pHandler = new COnHandleEventDelegate<T>();
            pHandler->m_pObject = pObject;
            pHandler->m_pOnHandleEventFunction = pOnHandleEventFunction;
            it->second.insert(pHandler);
        }        
    }
}

template <class T> void CEventDispatcher::UnRegisterHandler(int nEventId, T* pObject)
{
    auto it = m_mapEventId2Handlers.find(nEventId);
    if (it != m_mapEventId2Handlers.end())
    {
        for (auto itHandle = it->second.begin(); itHandle != it->second.end(); ++itHandle)
        {
            COnHandleEventDelegate<T>* pHandler = (COnHandleEventDelegate<T>*)*itHandle;
            if (pHandler->m_pObject == pObject)
            {
                delete pHandler;
                it->second.erase(itHandle);
                break;
            }
        }
    }
}

template <class T> void CEventDispatcher::UnRegisterHandler(T* pObject)
{
    for (auto it = m_mapEventId2Handlers.begin(); it != m_mapEventId2Handlers.end(); ++it)
    {
        for (auto itHandle = it->second.begin(); itHandle != it->second.end(); ++itHandle)
        {
            COnHandleEventDelegate<T>* pHandler = (COnHandleEventDelegate<T>*)*itHandle;
            if (pHandler->m_pObject == pObject)
            {
                delete pHandler;
                it->second.erase(itHandle);
                break;
            }
        }
    }
}
