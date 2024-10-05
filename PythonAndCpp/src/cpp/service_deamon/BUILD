load("@bazel_skylib//rules:copy_file.bzl", "copy_file")

cc_binary(
    name = "service_deamon",
    srcs = ["service_deamon_main.cpp"],
    data = [":em_service_plugin"],
    deps = [
        ":socket_event_lib",
        "//src/cpp/service_factory/common:RuntimeServiceFactoryCollector",
    ],
)

cc_library(
    name = "socket_event_lib",
    srcs = [
        "ZEventloop.cpp",
        "ZSocketEventHandler.cpp",
    ],
    hdrs = [
        "IEventHandler.h",
        "ZEventloop.h",
        "ZSocketEventHandler.h",
    ],
    visibility = ["__subpackages__"],
    deps = [
        "//src/cpp/utils:ServiceDispatcher",
        "//src/cpp/utils:Trace",
    ],
)

copy_file(
    name = "em_service_plugin",
    src = "//src/cpp/service_factory/em_service_factory:ZEmServiceFactoryRunTimePlugin",
    out = "service_plugins/ZEmServiceFactoryRunTimePlugin.so",
    allow_symlink = True,
)
