#ifndef _I_SERVICE_FACTORY_COLLECTOR_
#define _I_SERVICE_FACTORY_COLLECTOR_

#include <map>
#include <string>

#include "src/cpp/service_factory/common/IServiceFactory.h"

using ServiceFactoryCollectionT =
    std::map<std::string, std::shared_ptr<IServiceFactory>>;

#endif