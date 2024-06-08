#ifndef _Z_SERVICE_PACKAGE_H_
#define _Z_SERVICE_PACKAGE_H_

#include <cstdint>
#include <string>
#include <vector>

// Little Endian
// Request:
// -------------------------------------------------------------------------------------------------
// | "Zed" | 4 byte length | 4 bytes service name length | service name | method index | input data|
// ------------------------------------------------------------------------------------------------
// Response:
// --------------------------------------------------------------------------------------------------
// | "Zed" | 4 byte length | 4 bytes service name length | service name | method index | output data|
// --------------------------------------------------------------------------------------------------

namespace ZServicePackage
{
  /* Function:                                                            *
   *  Pack - Package whole package                                        *
   * Params:                                                              *
   *  service_name(in):                                                   *
   *  method_index(in):                                                   *
   *  serialized_data(in):                                                *
   * Return value:                                                        *
   *  SUCCESS: Vector, bin package included                               *
   *  FAIL:    Empty vector                                               *
  */
  std::vector<uint8_t> Pack(
    const std::string& service_name,
    const uint32_t method_index,
    const std::vector<uint8_t>& serialized_data);

  /* Function:                                                            *
   *  Unpack - Unpack the package                                         *
   * Params:                                                              *
   *  package_data(in):                                                   *
   *  service_name(out):                                                  *
   *  method_index(out):                                                  *
   * Return value:                                                        *
   *  SUCCESS: vector, serialized data included                           *
   *  FAIL:    Empty vector                                               *
  */
  std::vector<uint8_t> Unpack(
     const std::vector<uint8_t> package_data,
     std::string& service_name,
     uint32_t& method_index);

}

#endif
