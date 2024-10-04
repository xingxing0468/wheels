// CopyRight of ZED, All Rights Reserved

#ifndef _I_EVENT_HANDLER_H_
#define _I_EVENT_HANDLER_H_

class IEventHandler
{
public:
  virtual void HandleEvent(int fd) = 0;
};
#endif
