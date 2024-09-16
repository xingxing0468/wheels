cc_library(
    name = "ServiceUtils",
    visibility = ["//src/cpp:__subpackages__"],
    deps = [
        ":ServiceDispatcher",
        ":ServicePackage",
    ],
)

cc_library(
    name = "ServiceDispatcher",
    srcs = [
        "ZServiceDispatcher.cpp",
    ],
    hdrs = [
        "ZServiceDispatcher.h",
    ],
    visibility = ["//src/cpp:__subpackages__"],
    deps = [
        ":ServicePackage",
        "//src/cpp/service_factory/common:RuntimeServiceFactoryCollector",
        "@com_google_protobuf//:protobuf",
    ],
)

cc_library(
    name = "ServicePackage",
    srcs = [
        "ZServicePackage.cpp",
    ],
    hdrs = [
        "ZServicePackage.h",
    ],
    visibility = ["//src/cpp:__subpackages__"],
    deps = [
        "//src/cpp/service_factory/common:RuntimeServiceFactoryCollector",
    ],
)

filegroup(
    name = "z_utils_srcs",
    srcs = [
        "ZServiceDispatcher.cpp",
        "ZServicePackage.cpp",
    ],
    visibility = ["//:__subpackages__"],
)
