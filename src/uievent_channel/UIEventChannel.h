#pragma once
#include <string>
#include <map>
#include <set>
#include <windef.h>
#include "json.h"

/**
事件处理接口
*/
class IUIEventHandler
{
public:
    /**
    @name 事件处理接口
    @param strEventName 事件名字
    @param eventDataValue 事件数据
    */
    virtual void OnUIEventArrive(const std::string& strEventName, const Json::Value& eventDataValue) = 0;
};

/**
UI事件通道，提供发送事件、处理事件的通道机制
除了SendUIEvent可以在非UI线程调用外，其他接口必须在UI线程中调用
*/
class CUIEventChannel
{
private:
    CUIEventChannel();
    ~CUIEventChannel();

public:
    /**
    @name 获取单例对象
    */
    static CUIEventChannel* GetInstance();

    /**
    @name 初始化，必须在UI线程调用
    */
    bool Init();

    /**
    @name 发送事件
    @param strEventName 事件名字
    @param eventDataValue 事件数据
    @param bSync true同步（事件处理完成后返回） fasle异步（无需等事件处理完成）
    */
    void SendUIEvent(const std::string& strEventName, const Json::Value& eventDataValue, bool bSync);

    /**
    @name 注册处理器
    @param strEventName 事件名字
    @param pHandler 事件处理器，处理strEventName指定的事件
    */
    void RegisterHandler(const std::string& strEventName, IUIEventHandler* pHandler);

    /**
    @name 解注册处理器
    @param pHandler 事件处理器
    @param strEventName 事件名字，默认为空串未指定事件名字，将解注册所有pHandler不再处理任何事件
    */
    void UnRegisterHandler(IUIEventHandler* pHandler, const std::string& strEventName="");

private:
    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
    std::map<std::string, std::set<IUIEventHandler*>> m_mapEventName2Handler;
    HWND m_hMessageWindowHandle = NULL;
    WNDPROC m_pOldProc = nullptr;
};

