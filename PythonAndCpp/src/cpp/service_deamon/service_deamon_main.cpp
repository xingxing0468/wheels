#include <csignal>

#include "src/cpp/service_deamon/ZEventloop.h"
#include "src/cpp/service_deamon/ZSocketEventHandler.h"
#include "src/cpp/service_factory/common/ZRuntimeServiceFactoryCollector.h"
#include "src/cpp/utils/Trace.h"

ZSocketEventHandler* g_event_hanlder_ptr = nullptr;

void SignalHandler(int /*signum*/) {
  TRACE("Signal interupt received, cleanup and exit...");
  if (g_event_hanlder_ptr) {
    g_event_hanlder_ptr->CleanUp();
  }
  exit(0);
  return;
}

int main() {
  ZEventloop eventloop{};
  ZServiceDispatcher service_dispatcher{};
  ZSocketEventHandler event_handler{eventloop, service_dispatcher};

  g_event_hanlder_ptr = &event_handler;
  signal(SIGINT, SignalHandler);
  service_dispatcher.ResetServiceFactories<ZRuntimeServiceFactoryCollector>(
      "/tmp/service_plugins");
  eventloop.Run();

  return 0;
}