#include "stdafx.h"
#include <future>
#include "Task.h"

using namespace std;

CTask::CTask()
{
}

CTask::~CTask()
{
}

void CTask::SetCallback(ITaskCompleteCallback* pCallback)
{
    m_pCallback.store(pCallback);
}

bool CTask::Start(const std::string& strParam1, const std::string& strParam2)
{
    m_strParam1 = strParam1;
    m_strParam2 = strParam2;
    try
    {
        async(launch::async, &CTask::DoTask, this);
        return true;
    }
    catch (system_error err)
    {
        //启动线程失败，这里可以打些日志        
    }

    return false;
}

void CTask::Stop()
{
    SetCallback(nullptr);
}

void CTask::DoTask(CTask* pTask)
{
    //这里可以做一些耗时任务，具体与业务有关，比如同步等待进行HTTP请求，无法取消只能等HTTP请求底层库的返回
    //底层库返回后回调，回调前务必判断回调对象是否已经设置为空
    string strResult1 = "";
    bool bResult2 = true;
    int nResult3 = 10;
    ITaskCompleteCallback* pCallback = pTask->m_pCallback.load();
    if (pCallback != nullptr)
    {
        pCallback->OnTaskComplete(strResult1, bResult2, nResult3);
    }
    delete pTask;
}