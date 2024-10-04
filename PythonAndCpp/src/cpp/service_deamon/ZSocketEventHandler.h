#ifndef _Z_SOCKET_EVENT_HANDLER_H_
#define _Z_SOCKET_EVENT_HANDLER_H_

#include <string>

#include "src/cpp/service_deamon/IEventHandler.h"
#include "src/cpp/service_deamon/ZEventloop.h"
#include "src/cpp/utils/ZServiceDispatcher.h"

class ZSocketEventHandler : public IEventHandler {
 public:
  ZSocketEventHandler(ZEventloop& eventloop, const ZServiceDispatcher& dispatcher);
  ~ZSocketEventHandler();

  void HandleEvent(int fd) override;

 private:
  void HandleConnect();  // Current always allow connect request, TODO accepted
                         // error handling
  void HandleCall();
  int ReceiveAllFromSocket(int fd, uint8_t* buffer, int length);

  std::string server_socket_name_{};
  int server_socket_fd_{-1};
  int server_accepted_fd_{-1};
  ZEventloop& eventloop_;
  const ZServiceDispatcher& dispatcher_;
};

#endif