#include "src/cpp/service_deamon/ZEventloop.h"
#include "src/cpp/service_deamon/ZSocketEventHandler.h"
#include "src/cpp/service_factory/common/ZRuntimeServiceFactoryCollector.h"

int main() {
  ZEventloop eventloop{};
  ZServiceDispatcher service_dispatcher{};
  ZSocketEventHandler event_handler{eventloop, service_dispatcher};

  service_dispatcher.ResetServiceFactories<ZRuntimeServiceFactoryCollector>(
      "src/cpp/service_deamon/service_plugins");
  eventloop.Run();

  return 0;
}