#include "ZServicePackage.h"

#include <memory.h>

namespace ZServicePackage {

static const std::string Magic = "Zed";

static int GetPackageHeaderSize()
{
  // Magic length + 4 byte package size + 4 byte service name size
  return Magic.size() + sizeof(uint32_t) + sizeof(uint32_t);
};

std::vector<uint8_t> Pack(
  const std::string& service_name,
  const uint32_t method_index,
  const std::vector<uint8_t>& serialized_data)
{
  std::vector<uint8_t> ret{};

  ret.assign(Magic.data(), Magic.data() + Magic.size()); // Signature
  uint32_t service_name_size = service_name.size();

  uint32_t package_size = 
    GetPackageHeaderSize() +
    service_name_size +
    sizeof(uint32_t) + // method index
    serialized_data.size();

  ret.insert(ret.end(), 
             reinterpret_cast<uint8_t*>(&package_size),
             reinterpret_cast<uint8_t*>(&package_size) + sizeof(uint32_t));

  ret.insert(ret.end(), 
             reinterpret_cast<uint8_t*>(&service_name_size),
             reinterpret_cast<uint8_t*>(&service_name_size) + sizeof(uint32_t));

  ret.insert(ret.end(),
             service_name.c_str(),
             service_name.c_str() + service_name.size());

  ret.insert(ret.end(),
             reinterpret_cast<const uint8_t*>(&method_index),
             reinterpret_cast<const uint8_t*>(&method_index) + sizeof(uint32_t));

  ret.insert(ret.end(),
             serialized_data.data(),
             serialized_data.data() + serialized_data.size());
  return ret;
};

std::vector<uint8_t> Unpack(
   const std::vector<uint8_t> package_data,
   std::string& service_name,
   uint32_t& method_index)
{
  std::vector<uint8_t> ret{};
  if (package_data.size() < GetPackageHeaderSize()) {
    return ret;
  }

  int offset = 0;
  if (memcmp(package_data.data(), Magic.data(), Magic.size())) { // Signature mismatch
    return ret;
  }
  offset += Magic.size();

  uint32_t package_size{0};
  memcpy(&package_size, package_data.data() + offset, sizeof(uint32_t));
  if (package_data.size() != package_size) { // Package size mismatch
    return ret;
  }
  offset += sizeof(uint32_t);

  uint32_t service_name_size{0};
  memcpy(&service_name_size, package_data.data() + offset, sizeof(uint32_t));
  offset += sizeof(uint32_t);
  
  service_name.clear();
  service_name.assign(package_data.data() + offset, package_data.data() + offset + service_name_size);
  offset += service_name_size;

  memcpy(&method_index, package_data.data() + offset, sizeof(uint32_t));
  offset += sizeof(uint32_t);

  ret.assign(package_data.begin() + offset, package_data.end());
}

}
