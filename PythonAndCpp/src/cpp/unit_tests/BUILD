cc_test(
    name = "utils_unit_test",
    srcs = [
        "TestServiceDispatcher.cpp",
        "TestServicePackage.cpp",
    ],
    copts = [
        "-Iexternal/gtest/googletest/include",
        "-Iexternal/gtest/googletest",
    ],
    deps = [
        "//src/cpp/utils:ServiceUtils",
        "@com_google_googletest//:gtest_main",
    ],
)
