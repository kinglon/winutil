#include "ConcreteHandler.h"
#include "EventDefine.h"

CConcreteHandler::CConcreteHandler()
{
    //CEventDispatcher::GetInstance()->RegisterHandler(EVENTID_ONE, this);
    //CEventDispatcher::GetInstance()->RegisterHandler(EVENTID_TWO, this);
    CEventDispatcher::GetInstance()->RegisterHandler(EVENTID_ONE, this, &CConcreteHandler::HanldeOneEvent);
    CEventDispatcher::GetInstance()->RegisterHandler(EVENTID_TWO, this, &CConcreteHandler::HanldeTwoEvent);
}

CConcreteHandler::~CConcreteHandler()
{
    CEventDispatcher::GetInstance()->UnRegisterHandler(this);
}

void CConcreteHandler::OnHandleEvent(int nEventId, const std::string& strEventData)
{
    if (nEventId == EVENTID_ONE)
    {
        HanldeOneEvent(strEventData);
    }
    else if (nEventId == EVENTID_TWO)
    {
        HanldeTwoEvent(strEventData);
    }
}

void CConcreteHandler::HanldeOneEvent(const std::string& strEventData)
{
    //handle one event
}

void CConcreteHandler::HanldeTwoEvent(const std::string& strEventData)
{
    //handle two event
}

void CConcreteHandler::HanldeOneEvent(int nEventId, const std::string& strEventData)
{
    //handle one event
}

void CConcreteHandler::HanldeTwoEvent(int nEventId, const std::string& strEventData)
{
    //handle two event
}