// CopyRight of ZED, All Rights Reserved

#ifndef _Z_EVENTLOOP_H_
#define _Z_EVENTLOOP_H_

#include <map>

#include "src/cpp/service_deamon/IEventHandler.h"

class ZEventloop {
 public:
  ZEventloop();
  void Run();
  void AddFd(int fd, IEventHandler* handler);
  void RemoveFd(int fd);

 private:
  struct ZEventData {
    int Fd;
    IEventHandler* Handler;
  };

  // Fd as a identifier, to help remove/add
  typedef std::map<int, ZEventData> ZEventDataMap;

  // To identify when add, remmove and execute
  ZEventDataMap Events;
  const int EpollFd;
};

#endif
