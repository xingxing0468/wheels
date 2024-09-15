#ifndef _Z_STATIC_SERVICE_FACTORY_COLLECTOR_H_
#define _Z_STATIC_SERVICE_FACTORY_COLLECTOR_H_

#include "src/cpp/service_factory/common/IServiceFactoryCollector.h"

class ZStaticServiceFactoryCollector {
 public:
  static ServiceFactoryCollectionT FetchAvailableServiceFactories(
      const std::string& context = "");
};

#endif