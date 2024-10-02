#ifndef _I_SERVICE_FACTORY_COLLECTOR_
#define _I_SERVICE_FACTORY_COLLECTOR_

#include <map>
#include <string>

#include "exports/cpp/IServiceFactory.h"

using ServiceFactoryCollectionT =
    std::map<std::string, std::shared_ptr<IServiceFactory>>;

#endif