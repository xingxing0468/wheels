cc_binary(
    name = "service_deamon",
    srcs = ["service_deamon_main.cpp"],
    deps = [":socket_event_lib"],
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
