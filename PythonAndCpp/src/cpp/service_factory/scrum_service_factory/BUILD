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
    visibility = ["//src/cpp:__subpackages__"],
    deps = [":ZScrumServiceFactory"],
)

cc_shared_library(
    name = "ZScrumServiceFactoryRunTimePlugin",
    roots = [":ZScrumServiceFactoryRunTimeImpl"],
    visibility = ["//src:__subpackages__"],
)
