#pragma once
#include <string>
#include <map>
#include <set>
#include <windef.h>
#include "json.h"

/**
�¼�����ӿ�
*/
class IUIEventHandler
{
public:
    /**
    @name �¼�����ӿ�
    @param strEventName �¼�����
    @param eventDataValue �¼�����
    */
    virtual void OnUIEventArrive(const std::string& strEventName, const Json::Value& eventDataValue) = 0;
};

/**
UI�¼�ͨ�����ṩ�����¼��������¼���ͨ������
����SendUIEvent�����ڷ�UI�̵߳����⣬�����ӿڱ�����UI�߳��е���
*/
class CUIEventChannel
{
private:
    CUIEventChannel();
    ~CUIEventChannel();

public:
    /**
    @name ��ȡ��������
    */
    static CUIEventChannel* GetInstance();

    /**
    @name ��ʼ����������UI�̵߳���
    */
    bool Init();

    /**
    @name �����¼�
    @param strEventName �¼�����
    @param eventDataValue �¼�����
    @param bSync trueͬ�����¼�������ɺ󷵻أ� fasle�첽��������¼�������ɣ�
    */
    void SendUIEvent(const std::string& strEventName, const Json::Value& eventDataValue, bool bSync);

    /**
    @name ע�ᴦ����
    @param strEventName �¼�����
    @param pHandler �¼�������������strEventNameָ�����¼�
    */
    void RegisterHandler(const std::string& strEventName, IUIEventHandler* pHandler);

    /**
    @name ��ע�ᴦ����
    @param pHandler �¼�������
    @param strEventName �¼����֣�Ĭ��Ϊ�մ�δָ���¼����֣�����ע������pHandler���ٴ����κ��¼�
    */
    void UnRegisterHandler(IUIEventHandler* pHandler, const std::string& strEventName="");

private:
    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
    std::map<std::string, std::set<IUIEventHandler*>> m_mapEventName2Handler;
    HWND m_hMessageWindowHandle = NULL;
    WNDPROC m_pOldProc = nullptr;
};

