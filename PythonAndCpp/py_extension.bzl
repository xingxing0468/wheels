load("@rules_cc//cc:action_names.bzl", "C_COMPILE_ACTION_NAME")

def _compile_impl(ctx):
    # env = cc_common.get_environment_variables(
    #     feature_configuration = feature_configuration,
    #     action_name = C_COMPILE_ACTION_NAME,
    #     variables = variables,
    # )
    args = [f.path for f in ctx.files.setup_files] + ["--quiet", "build_ext", "--inplace"]
    # ld_library_path = [f.path for f in ctx.files.deps]

    # TODO: Use hermetic python
    ctx.actions.run_shell(
        outputs = [ctx.outputs.out],
        inputs = ctx.files.setup_files + ctx.files.input_files + ctx.files.deps,
        # command = " ".join(["python3"] + args) + " LD_LIBRARY_PATH=" + " ".join(ld_library_path) + ":${LD_LIBRARY_PATH}",
        command = " ".join(["python3"] + args),
        use_default_shell_env = True,
    )

z_comm_py_extension = rule(
    implementation = _compile_impl,
    attrs = {
        "setup_files": attr.label_list(
            mandatory = True,
            allow_files = True,
        ),
        "input_files": attr.label_list(allow_files = True),
        "out": attr.output(mandatory = True),
        "deps": attr.label_list(),
    },
    toolchains = [
        "@rules_python//python:toolchain_type",
    ],
)
