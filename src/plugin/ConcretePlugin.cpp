#pragma once
#include "ConcretePlugin.h"
#include "PluginClassInfo.h"

DEFINE_PLUGIN("ConcretePlugin", CConcretePlugin)

CConcretePlugin::CConcretePlugin(const std::string& strId)
{
    m_strId = strId;
}

IPlugin* CConcretePlugin::NewInstance(const std::string& strId)
{
    return new CConcretePlugin(strId);
}