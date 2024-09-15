cc_test(
    name = "service_dispatcher_test",
    srcs = [
        "TestServiceDispatcher.cpp",
    ],
    copts = [
        "-Iexternal/gtest/googletest/include",
        "-Iexternal/gtest/googletest",
    ],
    data = [
        "//src/cpp/service_factory/scrum_service_factory:ZScrumServiceFactoryRunTimeImpl",
    ],
    deps = [
        "//src/cpp/service_factory/common:RuntimeServiceFactoryCollector",
        "//src/cpp/service_factory/common:StaticServiceFactoryCollector",
        "//src/cpp/utils:ServiceDispatcher",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "service_package_test",
    srcs = [
        "TestServicePackage.cpp",
    ],
    copts = [
        "-Iexternal/gtest/googletest/include",
        "-Iexternal/gtest/googletest",
    ],
    deps = [
        "//src/cpp/utils:ServicePackage",
        "@com_google_googletest//:gtest_main",
    ],
)
