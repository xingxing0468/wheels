#ifndef _Z_SCRUM_SERVICE_FACTORY_H_
#define _Z_SCRUM_SERVICE_FACTORY_H_

#include "IServiceFactory.h"
#include "service_implementation/ZScrumService.h"

class ZScrumServiceFactory: public IServiceFactory
{
public:
  std::shared_ptr<google::protobuf::Service> GenerateServiceInstance() override
  {
    return std::make_shared<ZScrumService>();
  }
};

#endif