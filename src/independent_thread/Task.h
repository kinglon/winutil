#pragma once
#include <string>
#include <atomic>

/**
������ɻص��ӿ�
*/
class ITaskCompleteCallback
{
public:
    /**
    @name �������ʱ�ص��ӿ�
    @param ������ɵĽ��������ҵ����Ҫ���壬����ֻ�Ǿ���˵��
    */
    virtual void OnTaskComplete(const std::string& strParam1, bool bParam2, int nParam3) = 0;
};

/**
�����࣬��װ�����̵߳Ĵ�����Client����ʵ����CTask�����ͷ�CTask��������������Ƿ�ɹ��йأ����忴Start�����ע��˵��
*/
class CTask
{
public:
    CTask();
    ~CTask();

public:
    /**
    @name  ���ûص�����
    */
    void SetCallback(ITaskCompleteCallback* pCallback);

    /**
    @name ���������ڲ��ᴴ�����߳���������
    @param ����ҵ����Ҫ���壬����ֻ�Ǿ���˵��
    @return ������������ɹ���CTask���ʱһ����ص���ɽ����Ȼ���ͷ�CTask����
    �����������ʧ�ܣ�CTask���󲻻�ص���Client�����ͷ�CTask����
    */
    bool Start(const std::string& strParam1, const std::string& strParam2);
    
    /**
    @name ֹͣ���񣬵ȼ���SetCallback(nullptr)
    */
    void Stop();

private:
    /**
    @name ���߳���ں�����������ʹ��C++11 async�����߳�
    @param Start�ӿڵĲ���
    @param pTask task����
    */
    static void DoTask(std::string strParam1, std::string strParam2, CTask* pTask);

private:
    std::atomic<ITaskCompleteCallback*> m_pCallback = nullptr;  //ʹ��C++11��atomic�����ص�ָ��
};

