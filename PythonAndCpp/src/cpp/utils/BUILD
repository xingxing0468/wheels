cc_library(
    name = "ServiceUtils",
    srcs = [
        "ZServiceDispatcher.cpp",
        "ZServicePackage.cpp",
    ],
    hdrs = [
        "ZServiceDispatcher.h",
        "ZServicePackage.h",
    ],
    visibility = ["//src/cpp:__subpackages__"],
    deps = [
        "//src/cpp/service_factory/common:RuntimeServiceFactoryCollector",
        "//src/cpp/service_factory/common:StaticServiceFactoryCollector",
    ],
)
