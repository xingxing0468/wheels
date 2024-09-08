#ifndef _Z_STATIC_SERVICE_FACTORY_COLLECTOR_H_
#define _Z_STATIC_SERVICE_FACTORY_COLLECTOR_H_

#include "src/cpp/service_factory/IServiceFactoryCollector.h"
#include "src/cpp/service_factory/ZEmServiceFactory.h"
#include "src/cpp/service_factory/ZScrumServiceFactory.h"

namespace ZStaticServiceFactoryCollector {

ServiceFactoryCollectionT FetchAvailableServiceFactories() {
  return {{std::string("Scrum"), std::make_shared<ZScrumServiceFactory>()},
          {std::string("Em"), std::make_shared<ZEmServiceFactory>()}};
};

}  // namespace ZStaticServiceFactoryCollector

#endif