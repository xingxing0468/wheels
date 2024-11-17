load("@bazel_skylib//:bzl_library.bzl", "bzl_library")

cc_library(
    name = "cc_service_factory_common",
    includes = [
        "exports/cpp",
    ],
    visibility = ["//visibility:public"],
    deps = ["@zed_python_cpp//exports/cpp:ServicesFactory"],
)

bzl_library(
    name = "rules_bzl",
    srcs = [
        "@zed_python_cpp//exports/shell:deploy_service_plugins.bzl",
    ],
    visibility = ["//visibility:public"],
)
