py_binary(
    name = "example",
    srcs = ["example.py"],
    data = [
        "//src/cpp/service_factory/scrum_service_factory:ZScrumServiceFactoryRunTimePlugin",
    ],
    deps = [
        "//src/python/service_client",
        "//src/python/service_probe",
    ],
)
