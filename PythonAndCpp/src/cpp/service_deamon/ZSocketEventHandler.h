#ifndef _Z_SOCKET_EVENT_HANDLER_H_
#define _Z_SOCKET_EVENT_HANDLER_H_

#include <string>

#include "src/cpp/service_deamon/IEventHandler.h"
#include "src/cpp/service_deamon/ZEventloop.h"
#include "src/cpp/utils/ZServiceDispatcher.h"

class ZSocketEventHandler : public IEventHandler {
 public:
  ZSocketEventHandler(ZEventloop& eventloop,
                      const ZServiceDispatcher& dispatcher);
  ~ZSocketEventHandler();

  void HandleEvent(int fd) override;
  void Init();
  void CleanUp();

 private:
  void HandleConnect();  // Current always allow connect request, TODO accepted
                         // error handling
  void HandleCall();
  std::vector<std::uint8_t> ReceiveAllFromSocket();
  int SendAllToSocket(const std::vector<std::uint8_t>& data);

  std::string server_socket_name_{};
  int server_socket_fd_{-1};
  int server_accepted_fd_{-1};  // Only one connection is supported,
                                // TODO: support multi fds for multi-connections
  ZEventloop& eventloop_;
  const ZServiceDispatcher& dispatcher_;
};

#endif