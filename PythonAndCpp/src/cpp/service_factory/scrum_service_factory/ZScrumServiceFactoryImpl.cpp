#include "src/cpp/service_factory/scrum_service_factory/ZScrumServiceFactory.h"

extern "C" {
std::string GetServiceName() { return {"Scrum"}; }

std::shared_ptr<IServiceFactory> GetServiceFactory() {
  return std::make_shared<ZScrumServiceFactory>();
}
}