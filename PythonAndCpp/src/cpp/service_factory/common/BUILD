cc_library(
    name = "ServicesFactory",
    srcs = [
        "ServiceFactory.cpp",
    ],
    hdrs = [
        "IServiceFactory.h",
        "IServiceFactoryCollector.h",
    ],
    visibility = ["//src/cpp:__subpackages__"],
)

cc_library(
    name = "StaticServiceFactoryCollector",
    srcs = [
        "ZStaticServiceFactoryCollector.cpp",
    ],
    hdrs = [
        "ZStaticServiceFactoryCollector.h",
    ],
    visibility = ["//src/cpp:__subpackages__"],
    deps = [
        "//src/cpp/service_factory/em_service_factory:ZEmServiceFactory",
        "//src/cpp/service_factory/scrum_service_factory:ZScrumServiceFactory",
    ],
)

cc_library(
    name = "RuntimeServiceFactoryCollector",
    srcs = [
        "ZRuntimeServiceFactoryCollector.cpp",
    ],
    hdrs = [
        "ZRuntimeServiceFactoryCollector.h",
    ],
    visibility = ["//src/cpp:__subpackages__"],
    deps = [":ServicesFactory"],
)
