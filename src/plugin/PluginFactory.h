#pragma once
#include "IPlugin.h"

class CPluginFactory
{
public:
    CPluginFactory();
    ~CPluginFactory();

public:
    /**
    @name 创建插件
    @param strId 插件ID
    @return 创建失败返回nullptr
    */
    static IPlugin* CreatePlugin(const std::string& strId);

    /**
    @name 释放插件
    @param pPlugin 插件对象
    */
    static void DeletePlugin(IPlugin* pPlugin);
};