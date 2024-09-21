load("@pybind11_bazel//:build_defs.bzl", "pybind_extension")

filegroup(
    name = "z_comm",
    srcs = [
        "z_comm.cpp",
    ],
    visibility = ["//:__subpackages__"],
)

pybind_extension(
    name = "zprobe",
    srcs = [
        "//src/cpp/probe:z_probe",
        "//src/cpp/py_binding:z_comm",
    ],
    visibility = ["//:__subpackages__"],
    deps = [
        "//src/cpp/probe:Probe",
    ],
)
