load("//src/cpp/service_deamon:deploy_service_plugins.bzl", "local_deploy_service_plugin")

cc_library(
    name = "ZScrumServiceFactory",
    srcs = ["ZScrumServiceFactory.cpp"],
    hdrs = ["ZScrumServiceFactory.h"],
    visibility = ["//src/cpp:__subpackages__"],
    deps = [
        "//exports/cpp:ServicesFactory",
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

local_deploy_service_plugin(
    plugins = [":ZScrumServiceFactoryRunTimePlugin"],
    plugins_name = "ScrumServicePlugin",
)
