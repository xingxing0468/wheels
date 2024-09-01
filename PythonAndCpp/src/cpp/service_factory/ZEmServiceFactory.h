#ifndef _Z_EM_SERVICE_FACTORY_H_
#define _Z_EM_SERVICE_FACTORY_H_

#include "src/cpp/service_factory/IServiceFactory.h"
#include "src/cpp/service_implementation/ZEmService.h"

class ZEmServiceFactory : public IServiceFactory {
 public:
  std::shared_ptr<google::protobuf::Service> GenerateServiceInstance()
      override {
    return std::make_shared<ZEmService>();
  }
};

#endif