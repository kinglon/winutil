#pragma once
#include <string>

class IPlugin
{
public:
    virtual ~IPlugin() {}

public:
    /**
    @name �������
    @param strParamJson �������Я���Ĳ���
    @return �ɹ���ʧ��
    */
    virtual bool Start(const std::string& strParamJson) = 0;

    /**
    @name ֹͣ���
    */
    virtual void Stop() = 0;

    /**
    @name �ж��Ƿ�����
    @return true�������У�false��ֹͣ
    */
    virtual bool IsRunning() = 0;

    /**
    @name ��ȡ���ID
    @return ���ID
    */
    virtual std::string GetId() = 0;
};