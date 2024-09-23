#include "src/cpp/service_factory/common/ZStaticServiceFactoryCollector.h"

#include "src/cpp/service_factory/em_service_factory/ZEmServiceFactory.h"
#include "src/cpp/service_factory/scrum_service_factory/ZScrumServiceFactory.h"

ServiceFactoryCollectionT
ZStaticServiceFactoryCollector::FetchAvailableServiceFactories(
    const std::string& /*context*/) {
  return {{std::string("Scrum"), std::make_shared<ZScrumServiceFactory>()},
          {std::string("Em"), std::make_shared<ZEmServiceFactory>()}};
}