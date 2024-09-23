## TODO: make the deps built from source,
## Otherwise the symbols are missing due to the missing of cc_library deps.
## Seperate the proto buf deps and service impl into plug-ins.
## Then the py_binding will be more independent.
py_library(
    name = "service_probe",
    srcs = [
        "i_service_probe.py",
        "service_probe.py",
    ],
    data = [
        "//src/cpp/py_binding:zprobe.so",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//src/python/service_client",
    ],
)
