#pragma once
#include <string>

class IPlugin
{
public:
    virtual ~IPlugin() {}

public:
    /**
    @name 启动插件
    @param strParamJson 启动插件携带的参数
    @return 成功或失败
    */
    virtual bool Start(const std::string& strParamJson) = 0;

    /**
    @name 停止插件
    */
    virtual void Stop() = 0;

    /**
    @name 判断是否运行
    @return true正在运行，false已停止
    */
    virtual bool IsRunning() = 0;

    /**
    @name 获取插件ID
    @return 插件ID
    */
    virtual std::string GetId() = 0;
};