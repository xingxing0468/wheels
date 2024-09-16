#include <inttypes.h>
#include <memory.h>
#include <stdio.h>

#include <string>

#include "src/cpp/service_factory/common/ZRuntimeServiceFactoryCollector.h"
#include "src/cpp/utils/ZServiceDispatcher.h"

namespace {
ZServiceDispatcher g_dispatcher{};
}

void ResetServiceFactories(const std::string& context) {
  g_dispatcher.ResetServiceFactories<ZRuntimeServiceFactoryCollector>(context);
};

int OnServiceRequestReceived(const char* input_data, const int input_size,
                             char output[]) {
  auto ret_vector = g_dispatcher.Dispatch(
      std::vector<uint8_t>(input_data, input_data + input_size));
  memcpy(output, ret_vector.data(), ret_vector.size());
  return ret_vector.size();
}
