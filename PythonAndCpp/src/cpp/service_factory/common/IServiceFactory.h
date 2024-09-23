#ifndef _I_SERVICE_FACTORY_
#define _I_SERVICE_FACTORY_

#include "google/protobuf/service.h"

#include <memory>

class IServiceFactory
{
public:
  virtual std::shared_ptr<google::protobuf::Service> GenerateServiceInstance() = 0;
};

#endif