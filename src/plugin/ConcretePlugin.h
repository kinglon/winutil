#pragma once
#include "IPlugin.h"

class CConcretePlugin: public IPlugin
{
public:
    CConcretePlugin(const std::string& strId);

public:
    //create instance static function
    static IPlugin* NewInstance(const std::string& strId);

public:  //implement IPlugin
    virtual bool Start(const std::string& strParamJson) override { return true; }
    virtual void Stop() override {}
    virtual bool IsRunning() override { return true; }
    virtual std::string GetId() { return m_strId; }

private:
    std::string m_strId;
};