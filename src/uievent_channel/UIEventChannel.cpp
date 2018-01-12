#include "stdafx.h"
#include "UIEventChannel.h"

using namespace std;

#ifndef NDEBUG
#define UIEVENT_ASSERT(condition) if (!(condition)) { DebugBreak(); }
#else
#define UIEVENT_ASSERT(condition) ((void)0)
#endif

//窗口消息ID
#define WM_UIEVENTCHANNEL       WM_USER+1000

CUIEventChannel::CUIEventChannel()
{
}

CUIEventChannel::~CUIEventChannel()
{
}

CUIEventChannel* CUIEventChannel::GetInstance()
{
    static CUIEventChannel* pInstance = new CUIEventChannel();
    return pInstance;
}

bool CUIEventChannel::Init()
{
    //只允许初始化一次
    static bool bAlreadyInit = false;
    if (bAlreadyInit)
    {
        return true;
    }
    bAlreadyInit = true;

    m_hMessageWindowHandle = ::CreateWindow(L"Message", NULL, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, NULL, 0);
    if (m_hMessageWindowHandle == NULL)
    {
        UIEVENT_ASSERT(false);
        return false;
    }
    
    m_pOldProc = (WNDPROC)::SetWindowLong(m_hMessageWindowHandle, GWL_WNDPROC, (LONG)WindowProc);
    if (m_pOldProc== nullptr)
    {
        UIEVENT_ASSERT(false);
        return false;
    }

    return true;
}

void CUIEventChannel::SendUIEvent(const std::string& strEventName, const Json::Value& eventDataValue, bool bSync)
{    
    if (strEventName.empty() || m_hMessageWindowHandle == NULL)
    {
        UIEVENT_ASSERT(false);
        return;
    }

    string* pEventName = new string(strEventName);
    Json::Value* pEventDataValue = new Json::Value(eventDataValue);

    if (bSync)
    {
        SendMessage(m_hMessageWindowHandle, WM_UIEVENTCHANNEL, (WPARAM)pEventName, (LPARAM)pEventDataValue);
    }
    else
    {
        PostMessage(m_hMessageWindowHandle, WM_UIEVENTCHANNEL, (WPARAM)pEventName, (LPARAM)pEventDataValue);
    }
}

void CUIEventChannel::RegisterHandler(const std::string& strEventName, IUIEventHandler* pHandler)
{
    if (strEventName.empty() || pHandler == nullptr)
    {
        UIEVENT_ASSERT(false);
        return;
    }

    auto it = m_mapEventName2Handler.find(strEventName);
    if (it == m_mapEventName2Handler.end())
    {
        m_mapEventName2Handler[strEventName] = set < IUIEventHandler* >({pHandler});
    }
    else
    {
        it->second.insert(pHandler);
    }
}

void CUIEventChannel::UnRegisterHandler(IUIEventHandler* pHandler, const std::string& strEventName)
{
    if (pHandler == nullptr)
    {
        UIEVENT_ASSERT(false);
        return;
    }

    if (!strEventName.empty())
    {
        auto it = m_mapEventName2Handler.find(strEventName);
        if (it != m_mapEventName2Handler.end())
        {
            auto itHandler = it->second.find(pHandler);
            if (itHandler != it->second.end())
            {
                it->second.erase(itHandler);
            }
        }
    }
    else
    {
        for (auto it = m_mapEventName2Handler.begin(); it != m_mapEventName2Handler.end(); ++it)
        {
            auto itHandler = it->second.find(pHandler);
            if (itHandler != it->second.end())
            {
                it->second.erase(itHandler);
            }
        }
    }
}

LRESULT CALLBACK CUIEventChannel::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_UIEVENTCHANNEL)
    {
        string* pEventName = (string*)wParam;
        Json::Value* pEventDataValue = (Json::Value*)lParam;
        auto it = CUIEventChannel::GetInstance()->m_mapEventName2Handler.find(pEventName->c_str());
        if (it != CUIEventChannel::GetInstance()->m_mapEventName2Handler.end())
        {
            set<IUIEventHandler*> setHandlers = it->second;  //临时拷贝一份用来迭代，避免迭代处理事件过程中调用注册或解注册处理器接口导致迭代器失效
            for (auto itHandler = setHandlers.begin(); itHandler != setHandlers.end(); itHandler++)
            {
                (*itHandler)->OnUIEventArrive(pEventName->c_str(), *pEventDataValue);
            }
        }
        delete pEventName;
        delete pEventDataValue;
        return 1L;
    }
    else
    {
        return CallWindowProc(CUIEventChannel::GetInstance()->m_pOldProc, hWnd, message, wParam, lParam);
    }
}