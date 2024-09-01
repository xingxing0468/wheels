filegroup(
    name = "z_comm",
    srcs = [
        "z_comm.cpp",
    ],
    visibility = ["//:__subpackages__"],
)

cc_binary(
    name = "zprobe",
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
