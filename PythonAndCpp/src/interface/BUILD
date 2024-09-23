load("@build_stack_rules_proto//rules:proto_compile.bzl", "proto_compile")
load("@build_stack_rules_proto//rules/cc:proto_cc_library.bzl", "proto_cc_library")
load("@build_stack_rules_proto//rules/py:proto_py_library.bzl", "proto_py_library")
load("@rules_proto//proto:defs.bzl", "proto_library")

SERVICES = [
    "IEmService",
    "IScrumService",
]

proto_library(
    name = "interfaces",
    srcs = [service + ".proto" for service in SERVICES],
)

proto_compile(
    name = "cc_compiler",
    outputs = [
        service + ".pb.cc"
        for service in SERVICES
    ] + [service + ".pb.h" for service in SERVICES],
    plugins = ["@build_stack_rules_proto//plugin/builtin:cpp"],
    proto = "interfaces",
    visibility = ["__subpackages__"],
)

proto_cc_library(
    name = "cc_interfaces",
    srcs = [service + ".pb.cc" for service in SERVICES],
    hdrs = [service + ".pb.h" for service in SERVICES],
    visibility = ["//visibility:public"],
    deps = [
        "@com_google_protobuf//:protobuf",
    ],
)

proto_compile(
    name = "py_compiler",
    outputs = [
        service + "_pb2.py"
        for service in SERVICES
    ] + [service + "_pb2.pyi" for service in SERVICES],
    plugins = [
        "@build_stack_rules_proto//plugin/builtin:pyi",
        "@build_stack_rules_proto//plugin/builtin:python",
    ],
    proto = "interfaces",
    visibility = ["//visibility:public"],
)

proto_py_library(
    name = "py_interfaces",
    srcs = [service + "_pb2.py" for service in SERVICES],
    visibility = ["//visibility:public"],
    deps = [
        "@com_google_protobuf//:protobuf_python",
    ],
)
