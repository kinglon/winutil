#pragma once
#include "EventDispatcher.h"

class CConcreteHandler : public IOnHandleEvent
{
public:
    CConcreteHandler();
    ~CConcreteHandler();

public: //implement IOnHandleEvent
    virtual void OnHandleEvent(int nEventId, const std::string& strEventData) override;

private:
    void HanldeOneEvent(const std::string& strEventData);
    void HanldeTwoEvent(const std::string& strEventData);
    void HanldeOneEvent(int nEventId, const std::string& strEventData);
    void HanldeTwoEvent(int nEventId, const std::string& strEventData);
};

