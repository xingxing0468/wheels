#ifndef _Z_SERVICE_DISPATCHER_H_
#define _Z_SERVICE_DISPATCHER_H_

#include <cstdint>
#include <vector>

// clang-format off

namespace ZServiceDispatcher
{

  /* Function:                                                            *
    *  Dispatch - Dispatch the service call                                *
    * Params:                                                              *
    *  input_data(in):  input package data                                 *
    * Return value:                                                        *
    *  TO BE FILLED                                                        *
  */
  std::vector<uint8_t> Dispatch(const std::vector<uint8_t>& input_data);

} // namespace ZServiceDispatcher

#endif