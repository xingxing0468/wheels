#ifndef _Z_SERVICE_DISPATCHER_H_
#define _Z_SERVICE_DISPATCHER_H_

#include <cstdint>
#include <string>
#include <vector>

#include "src/cpp/service_factory/common/IServiceFactoryCollector.h"

class ZServiceDispatcher {
 public:
  static constexpr int MAX_PARAM_SERIALIZED_SIZE = 1024;
  template <class T>
  void ResetServiceFactories(const std::string& service_plugin_path = "") {
    service_factories_.clear();
    service_factories_ = T::FetchAvailableServiceFactories(service_plugin_path);
  };

  /* Function:                                                            *
   *  Dispatch - Dispatch the service call                                *
   * Params:                                                              *
   *  input_data(in):  input package data                                 *
   * Return value:                                                        *
   *  TO BE FILLED                                                        *
   */
  std::vector<uint8_t> Dispatch(const std::vector<uint8_t>& input_data) const;

 private:
  ServiceFactoryCollectionT service_factories_;
};

#endif