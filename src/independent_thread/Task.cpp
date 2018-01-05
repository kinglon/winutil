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
        //�����߳�ʧ�ܣ�������Դ�Щ��־        
    }

    return false;
}

void CTask::Stop()
{
    SetCallback(nullptr);
}

void CTask::DoTask(CTask* pTask)
{
    //���������һЩ��ʱ���񣬾�����ҵ���йأ�����ͬ���ȴ�����HTTP�����޷�ȡ��ֻ�ܵ�HTTP����ײ��ķ���
    //�ײ�ⷵ�غ�ص����ص�ǰ����жϻص������Ƿ��Ѿ�����Ϊ��
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