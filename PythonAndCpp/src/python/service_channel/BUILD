py_library(
    name = "local_service_channel",
    srcs = [
        "local_service_channel.py",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//src/python/service_client",
        "//src/python/service_probe:z_c_extension_service_probe",
    ],  # TODO: minimun dependency?
)

py_library(
    name = "ipc_service_channel",
    srcs = [
        "ipc_service_channel.py",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//src/python/service_client",
        "//src/python/service_probe:z_socket_service_probe",
    ],  # TODO: minimun dependency?
)
