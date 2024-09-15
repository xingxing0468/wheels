#include <inttypes.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <string>

constexpr int MAX_OUTPUT_DATA_SIZE = 0x10000;

extern void ResetServiceFactories(const std::string& context);
extern int OnServiceRequestReceived(const uint8_t* input_data,
                                    const int input_size, uint8_t output[]);

void ResetServiceFactories_pybind11(const std::string& context) {
  return ResetServiceFactories(context);
}

std::vector<std::uint8_t> OnServiceRequestReceived_pybind11(
    const std::vector<std::uint8_t>& input_data) {
  std::vector<std::uint8_t> ret{};
  uint8_t out_buff[MAX_OUTPUT_DATA_SIZE];
  const auto output_size{
      OnServiceRequestReceived(input_data.data(), input_data.size(), out_buff)};
  ret.insert(ret.end(), out_buff, out_buff + output_size);
  return ret;
}

PYBIND11_MODULE(zprobe, m) {
  m.def("reset_service_path", ResetServiceFactories_pybind11);
  m.def("communicate", OnServiceRequestReceived_pybind11);

  m.doc() = "Z Communication - Python integration";
}
