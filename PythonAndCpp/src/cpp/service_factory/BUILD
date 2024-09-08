cc_library(
    name = "ServicesFactory",
    srcs = ["ServiceFactory.cpp"],
    hdrs = [
        "IServiceFactory.h",
        "IServiceFactoryCollector.h",
        "ZEmServiceFactory.h",
        "ZScrumServiceFactory.h",
        "ZStaticServiceFactoryCollector.h",
    ],
    visibility = ["//src/cpp:__subpackages__"],
    deps = ["//src/cpp/service_implementation:ServicesImpl"],
)
