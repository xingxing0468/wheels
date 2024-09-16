load("//src/cpp/service_factory:service_plugin.bzl", "service_plugin")

cc_library(
    name = "ZScrumServiceFactory",
    srcs = ["ZScrumServiceFactory.cpp"],
    hdrs = ["ZScrumServiceFactory.h"],
    visibility = ["//src/cpp:__subpackages__"],
    deps = [
        "//src/cpp/service_factory/common:ServicesFactory",
        "//src/cpp/service_implementation/scrum_service:ScrumServicesImpl",
    ],
)

cc_library(
    name = "ZScrumServiceFactoryRunTimeImpl",
    srcs = ["ZScrumServiceFactoryImpl.cpp"],
    visibility = ["//src:__subpackages__"],
    deps = [":ZScrumServiceFactory"],
)

service_plugin(
    name = "ScrumServicePlugin",
    data = [
        # ":ZScrumServiceFactory",
        ":ZScrumServiceFactoryRunTimeImpl",
        # "//src/cpp/service_factory/em_service_factory:ZEmServiceFactoryRunTimeImpl",
    ],
    visibility = ["//src/cpp:__subpackages__"],
)
