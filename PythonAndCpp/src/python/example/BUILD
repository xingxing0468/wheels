load("@bazel_skylib//rules:copy_file.bzl", "copy_file")

py_binary(
    name = "example",
    srcs = ["example.py"],
    data = [
        ":em_service_plugin",
        ":scrum_service_plugin",
    ],
    deps = [
        "//src/python/service_client",
        "//src/python/service_probe",
    ],
)

copy_file(
    name = "scrum_service_plugin",
    src = "//src/cpp/service_factory/scrum_service_factory:ZScrumServiceFactoryRunTimePlugin",
    out = "service_plugins/ZScrumServiceFactoryRunTimePlugin.so",
    allow_symlink = True,
)

copy_file(
    name = "em_service_plugin",
    src = "//src/cpp/service_factory/em_service_factory:ZEmServiceFactoryRunTimePlugin",
    out = "service_plugins/ZEmServiceFactoryRunTimePlugin.so",
    allow_symlink = True,
)
