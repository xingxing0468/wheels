#ifndef _Z_SCRUM_SERVICE_FACTORY_H_
#define _Z_SCRUM_SERVICE_FACTORY_H_

#include "exports/cpp/IServiceFactory.h"
#include "src/cpp/service_implementation/scrum_service/ZScrumService.h"

class ZScrumServiceFactory : public IServiceFactory {
 public:
  std::shared_ptr<google::protobuf::Service> GenerateServiceInstance()
      const override {
    return std::make_shared<ZScrumService>();
  }
};

#endif