cc_binary(
    name = "py_binding",
    srcs = [
        "//src/cpp/py_binding:z_comm",
    ],
    copts = [
        "-fPIC",
    ],
    linkshared = 1,
    visibility = ["//:__subpackages__"],
    deps = [
        "//src/cpp/probe:Probe",
        "@pybind11//:pybind11_lib",
    ],
)

py_library(
    name = "py_binding_lib",
    data = [":py_binding"],
    imports = ["."],
    visibility = ["//visibility:private"],
)

py_library(
    name = "service_probe",
    srcs = [
        "i_service_probe.py",
        "service_probe.py",
    ],
    visibility = ["//:__subpackages__"],
    deps = [
        "//src/python/service_client",
        "//src/python/service_probe:py_binding_lib",
    ],
)
