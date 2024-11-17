load("//exports/shell:deploy_service_plugins.bzl", "local_deploy_service_plugin")

cc_library(
    name = "ZEmServiceFactory",
    srcs = ["ZEmServiceFactory.cpp"],
    hdrs = ["ZEmServiceFactory.h"],
    visibility = ["//src/cpp:__subpackages__"],
    deps = [
        "//exports/cpp:ServicesFactory",
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

local_deploy_service_plugin(
    plugins = [":ZEmServiceFactoryRunTimePlugin"],
    plugins_name = "EmServicePlugin",
)
