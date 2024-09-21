#include <inttypes.h>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/stl.h>

#include <string>

constexpr int MAX_OUTPUT_DATA_SIZE = 0x10000;

extern void ResetServiceFactories(const std::string& context);
extern int OnServiceRequestReceived(const char* input_data,
                                    const int input_size, char output[]);

void ResetServiceFactories_pybind11(const std::string& context) {
  return ResetServiceFactories(context);
}

pybind11::bytes OnServiceRequestReceived_pybind11(
    const pybind11::bytes& input_data) {
  char out_buff[MAX_OUTPUT_DATA_SIZE];
  const auto output_size{
      OnServiceRequestReceived(PyBytes_AsString(input_data.ptr()),
                               PyBytes_Size(input_data.ptr()), out_buff)};
  return {out_buff, output_size};
}

PYBIND11_MODULE(zprobe, m) {
  m.def("reset_service_path", &ResetServiceFactories_pybind11);
  m.def("communicate", &OnServiceRequestReceived_pybind11);

  m.doc() = "Z Communication - Python integration";
}
