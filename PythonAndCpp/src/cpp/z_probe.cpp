#include "utils/ZServiceDispatcher.h"

#include <inttypes.h>
#include <stdio.h>
#include <memory.h>

// clang-format off

extern "C"
{
    int OnServiceRequestReceived(
        const uint8_t* input_data,
        const int input_size,
        uint8_t output[])
    {
        auto ret_vector =
          ZServiceDispatcher::Dispatch(
              std::vector<uint8_t>(input_data,
                                   input_data + input_size));
        memcpy(output, ret_vector.data(), ret_vector.size());
        return ret_vector.size();
    }
}

