#include "src/cpp/service_factory/em_service_factory/ZEmServiceFactory.h"

extern "C" {
std::string GetServiceName() { return {"Em"}; }

std::shared_ptr<IServiceFactory> GetServiceFactory() {
  return std::make_shared<ZEmServiceFactory>();
}
}