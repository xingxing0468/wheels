cc_library(
    name = "ZEmServiceFactory",
    srcs = ["ZEmServiceFactory.cpp"],
    hdrs = ["ZEmServiceFactory.h"],
    visibility = ["//src/cpp:__subpackages__"],
    deps = [
        "//src/cpp/service_factory/common:ServicesFactory",
        "//src/cpp/service_implementation/em_service:EmServicesImpl",
    ],
)

cc_library(
    name = "ZEmServiceFactoryRunTimeImpl",
    srcs = ["ZEmServiceFactoryImpl.cpp"],
    visibility = ["//src/cpp:__subpackages__"],
    deps = [":ZEmServiceFactory"],
)

cc_shared_library(
    name = "ZEmServiceFactoryRunTimePlugin",
    roots = [":ZEmServiceFactoryRunTimeImpl"],
    visibility = ["//src:__subpackages__"],
)
