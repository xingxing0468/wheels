load("@bazel_skylib//rules:copy_file.bzl", "copy_file")

py_binary(
    name = "example_single_process",
    srcs = ["example_single_process.py"],
    data = [
        ":em_service_plugin",
        ":scrum_service_plugin",
    ],
    deps = [
        "//src/python/service_channel:local_service_channel",
    ],
)

py_binary(
    name = "example_socket_client",
    srcs = ["example_socket_client.py"],
    deps = [
        "//src/python/service_channel:ipc_service_channel",
    ],
)

copy_file(
    name = "scrum_service_plugin",
    src = "//src/cpp/service_factory/scrum_service_factory:ZScrumServiceFactoryRunTimePlugin",
    out = "service_plugins/ZScrumServiceFactoryRunTimePlugin.so",
    allow_symlink = True,
)

copy_file(
    name = "em_service_plugin",
    src = "//src/cpp/service_factory/em_service_factory:ZEmServiceFactoryRunTimePlugin",
    out = "service_plugins/ZEmServiceFactoryRunTimePlugin.so",
    allow_symlink = True,
)
