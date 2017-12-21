#pragma once
#include <string>
#include <map>
#include <set>
#include <assert.h>

/**
定义事件处理接口
*/
class IOnHandleEvent
{
public:
    /**
    @name 处理事件接口
    @param nEventId 事件ID
    @param strEventData 携带事件参数数据
    */
    virtual void OnHandleEvent(int nEventId, const std::string& strEventData) = 0;
};

/**
定义事件处理代理模板类
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
负责事件处理器注册/解注册、事件分发
*/
class CEventDispatcher
{
private:
    CEventDispatcher();
    ~CEventDispatcher();

public:
    /**
    @name 获取单例对象
    */
    static CEventDispatcher* GetInstance();

    /**
    @name 请求分发事件
    @param nEventId 事件ID
    @param strEventData 事件携带数据
    */
    void DispatchEvent(int nEventId, const std::string& strEventData);

    /**
    @name 注册事件处理器
    @param nEventId 事件ID
    @param pHandler 处理器
    */
    void RegisterHandler(int nEventId, IOnHandleEvent* pHandler);
    
    /**
    @name 解注册事件处理器
    @param nEventId 事件ID
    @param pHandler 处理器
    */
    void UnRegisterHandler(int nEventId, IOnHandleEvent* pHandler);

    /**
    @name 解注册指定处理器的所有事件
    @param pHandler 处理器
    */
    void UnRegisterHandler(IOnHandleEvent* pHandler);

    /**
    @name 注册事件处理器
    @param nEventId 事件ID
    @param pObject 处理器成员函数所属对象
    @param pOnHandleEventFunction 成员函数地址
    */
    template <class T> void RegisterHandler(int nEventId, T* pObject, void (T::*pOnHandleEventFunction)(int, const std::string&));

    /**
    @name 解注册事件处理器
    @param nEventId 事件ID
    @param pObject 处理器成员函数所属对象
    */
    template <class T> void UnRegisterHandler(int nEventId, T* pObject);

    /**
    @name 解注册指定对象的所有处理器
    @param pObject 处理器成员函数所属对象
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
                assert(false);  //多次注册
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
