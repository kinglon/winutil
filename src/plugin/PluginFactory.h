#pragma once
#include "IPlugin.h"

class CPluginFactory
{
public:
    CPluginFactory();
    ~CPluginFactory();

public:
    /**
    @name �������
    @param strId ���ID
    @return ����ʧ�ܷ���nullptr
    */
    static IPlugin* CreatePlugin(const std::string& strId);

    /**
    @name �ͷŲ��
    @param pPlugin �������
    */
    static void DeletePlugin(IPlugin* pPlugin);
};