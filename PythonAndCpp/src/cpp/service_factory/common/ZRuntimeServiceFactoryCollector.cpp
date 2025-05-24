#include "src/cpp/service_factory/common/ZRuntimeServiceFactoryCollector.h"

#include <dlfcn.h>
#include <stdio.h>

#include <filesystem>

#include "src/cpp/utils/Trace.h"

ServiceFactoryCollectionT
ZRuntimeServiceFactoryCollector::FetchAvailableServiceFactories(
    const std::string& context) {
  ServiceFactoryCollectionT ret{};

  std::string (*GetServiceName)(){nullptr};
  std::shared_ptr<IServiceFactory> (*GetServiceFactory)(){nullptr};

  const std::string service_name_func_name{"GetServiceName"};
  const std::string service_factory_func_name{"GetServiceFactory"};

  for (const auto& file :
       std::filesystem::directory_iterator{std::filesystem::path{context}}) {
    if (!file.is_regular_file()) {
      continue;
    }
    if (file.path().extension() != ".so") {
      continue;
    }
    void* service_factory_obj = dlopen(file.path().c_str(), RTLD_LAZY);
    if (!service_factory_obj) {
      TRACE("WARNING: Load lib file: [%s] failed, error: [%s] skip\n",
            file.path().c_str(), dlerror());
      continue;
    }

    // Service name
    void* service_name_func{
        dlsym(service_factory_obj, service_name_func_name.c_str())};
    if (!service_name_func) {
      TRACE("WARNING: Get symbol [%s] from lib file [%s] failed, skip.\n",
            service_name_func_name.c_str(), file.path().c_str());
      continue;
    }
    GetServiceName =
        reinterpret_cast<decltype(GetServiceName)>(service_name_func);
    const std::string service_name{(*GetServiceName)()};

    if (ret.find(service_name) != ret.end()) {
      TRACE(
          "WARNING: service name [%s] already loaded, skip to load lib file "
          "[%s].\n",
          service_name.c_str(), file.path().c_str());
      continue;
    }

    // Service factory
    void* service_factory_func{
        dlsym(service_factory_obj, service_factory_func_name.c_str())};
    if (!service_factory_func) {
      TRACE("WARNING: Get symbol [%s] from lib file [%s] failed, skip.\n",
            service_factory_func_name.c_str(), file.path().c_str());
      continue;
    }
    GetServiceFactory =
        reinterpret_cast<decltype(GetServiceFactory)>(service_factory_func);
    auto service_factory_ptr{(*GetServiceFactory)()};
    if (!service_factory_ptr) {
      TRACE(
          "WARNING: Get service factory ptr for service [%s] from lib file "
          "[%s] failed, skip.\n",
          service_name.c_str(), file.path().c_str());
      continue;
    }

    TRACE("Successfully loaded service [%s] from lib file [%s]\n",
          service_name.c_str(), file.path().c_str());
    ret[service_name] = service_factory_ptr;
  }

  return ret;
}
