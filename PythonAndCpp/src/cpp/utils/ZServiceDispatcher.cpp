
#include "src/cpp/utils/ZServiceDispatcher.h"

#include <map>

#include "google/protobuf/empty.pb.h"
#include "src/cpp/utils/ZServicePackage.h"

namespace {
constexpr int MAX_PARAM_SERIALIZED_SIZE = 1024;
std::map<std::string, std::shared_ptr<google::protobuf::Service>>
    CachedServiceInstances;
}  // namespace

std::vector<uint8_t> ZServiceDispatcher::Dispatch(
    const std::vector<uint8_t>& input_data) {
  google::protobuf::Message* request = nullptr;
  google::protobuf::Message* response = nullptr;

  auto cleanup = [&]() {
    if (request) {
      delete request;
    }
    if (response) {
      delete response;
    }
  };

  std::vector<uint8_t> ret;
  std::string service_name = "";
  uint32_t method_id = 0xFFFFFFFF;
  std::vector<uint8_t> serialized_input_param =
      ZServicePackage::Unpack(input_data, service_name, method_id);

  if (service_factories_.find(service_name) == service_factories_.end()) {
    // Serivce NOT supported
    printf("ERROR: service NOT supported\n");
    return ret;
  }

  if (CachedServiceInstances.find(service_name) ==
          CachedServiceInstances.end() ||
      !CachedServiceInstances[service_name]) {
    CachedServiceInstances[service_name] =
        service_factories_[service_name]->GenerateServiceInstance();
  }

  std::shared_ptr<google::protobuf::Service> service_ptr =
      CachedServiceInstances[service_name];

  if (method_id >= static_cast<std::uint32_t>(
                       service_ptr->GetDescriptor()->method_count())) {
    // Method id exceed the limit
    printf("ERROR: Method id exceed the limit\n");
    return ret;
  }

  const google::protobuf::MethodDescriptor* methodDes =
      service_ptr->GetDescriptor()->method(method_id);

  request = service_ptr->GetRequestPrototype(methodDes).New();
  response = service_ptr->GetResponsePrototype(methodDes).New();

  if (!request->ParseFromArray(serialized_input_param.data(),
                               serialized_input_param.size())) {
    // Fail to de-serialize input param
    printf("ERROR: Fail to de-serialize input param.\n");
    cleanup();
    return ret;
  }

  service_ptr->CallMethod(methodDes, nullptr, request, response, nullptr);
  if (!(response->GetDescriptor() ==
        google::protobuf::Empty::descriptor())) {  // NOT oneway call
    if (response->ByteSizeLong() > MAX_PARAM_SERIALIZED_SIZE) {
      // Exceed param serialized size
      printf("ERROR: Exceed param serialized size.\n");
      cleanup();
      return ret;
    }
    uint8_t buf[MAX_PARAM_SERIALIZED_SIZE];
    if (!response->SerializeToArray(buf, response->ByteSizeLong())) {
      // Serialization failed
      printf("ERROR: Output param serialization failed.\n");
      cleanup();
      return ret;
    }
    ret = ZServicePackage::Pack(
        service_name, method_id,
        std::vector<uint8_t>(buf, buf + response->ByteSizeLong()));
  }

  cleanup();
  return ret;
}