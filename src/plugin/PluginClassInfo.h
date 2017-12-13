#pragma once
#include "IPlugin.h"

class IPlugin;
typedef IPlugin*  (*FnCreatePluginInstance)(const std::string& strId);

class CPluginClassInfo
{
public:
    CPluginClassInfo(const std::string& strId, FnCreatePluginInstance pCreatorFun);
    ~CPluginClassInfo();

public:
    std::string m_strId;
    FnCreatePluginInstance m_pCreatorFun = nullptr;
    CPluginClassInfo* m_pNext = nullptr;
    static CPluginClassInfo* m_pFirst;
};

#define DEFINE_PLUGIN(ID, CLASSNAME)  CPluginClassInfo g_plugin_##CLASSNAME(ID, &CLASSNAME::NewInstance);