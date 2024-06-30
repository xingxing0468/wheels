load("@rules_proto//proto:defs.bzl", "proto_library")

proto_library(
    name = "interfaces",
    srcs = [
        "IEmService.proto",
        "IScrumService.proto",
    ],
)

cc_proto_library(
    name = "cc_interfaces",
    visibility = ["//src:__subpackages__"],
    deps = [":interfaces"],
)
