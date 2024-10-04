#include "src/cpp/service_deamon/ZEventloop.h"
#include "src/cpp/service_deamon/ZSocketEventHandler.h"

int main() {
  ZEventloop eventloop{};
  ZServiceDispatcher service_dispatcher{};
  ZSocketEventHandler event_handler{eventloop, service_dispatcher};

  eventloop.Run();

  return 0;
}