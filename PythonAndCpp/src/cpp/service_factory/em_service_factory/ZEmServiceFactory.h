#ifndef _Z_EM_SERVICE_FACTORY_H_
#define _Z_EM_SERVICE_FACTORY_H_

#include "exports/cpp/IServiceFactory.h"
#include "src/cpp/service_implementation/em_service/ZEmService.h"

class ZEmServiceFactory : public IServiceFactory {
 public:
  std::shared_ptr<google::protobuf::Service> GenerateServiceInstance()
      override {
    return std::make_shared<ZEmService>();
  }
};

#endif