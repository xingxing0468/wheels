load("//:py_extension.bzl", "z_comm_py_extension")

z_comm_py_extension(
    name = "probe_extension",
    out = "z_probe.so",
    input_files = ["z_comm.c"],
    setup_files = ["setup_zprobe.py"],
    deps = ["//src/cpp:Probe"],
)
