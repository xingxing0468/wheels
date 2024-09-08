#include "src/cpp/service_factory/em_service_factory/ZEmServiceFactory.h"

std::string GetServiceName() { return {"Em"}; }

std::shared_ptr<IServiceFactory> GetServiceFactory() {
  return std::make_shared<ZEmServiceFactory>();
}