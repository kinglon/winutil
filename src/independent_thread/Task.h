#pragma once
#include <string>
#include <atomic>

/**
任务完成回调接口
*/
class ITaskCompleteCallback
{
public:
    /**
    @name 任务完成时回调接口
    @param 任务完成的结果，根据业务需要定义，这里只是举例说明
    */
    virtual void OnTaskComplete(const std::string& strParam1, bool bParam2, int nParam3) = 0;
};

/**
任务类，封装了子线程的创建，Client负责实例化CTask对象，释放CTask对象跟任务启动是否成功有关，具体看Start结果的注释说明
*/
class CTask
{
public:
    CTask();
    ~CTask();

public:
    /**
    @name  设置回调对象
    */
    void SetCallback(ITaskCompleteCallback* pCallback);

    /**
    @name 启动任务，内部会创建子线程运行任务
    @param 根据业务需要定义，这里只是举例说明
    @return 如果任务启动成功，CTask完成时一定会回调完成结果，然后释放CTask对象，
    如果任务启动失败，CTask对象不会回调，Client负责释放CTask对象
    */
    bool Start(const std::string& strParam1, const std::string& strParam2);
    
    /**
    @name 停止任务，等价于SetCallback(nullptr)
    */
    void Stop();

private:
    /**
    @name 子线程入口函数，本例子使用C++11 async启动线程
    @param Start接口的参数
    @param pTask task对象
    */
    static void DoTask(std::string strParam1, std::string strParam2, CTask* pTask);

private:
    std::atomic<ITaskCompleteCallback*> m_pCallback = nullptr;  //使用C++11的atomic保护回调指针
};

