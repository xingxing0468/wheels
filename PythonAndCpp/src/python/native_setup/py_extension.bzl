load("@rules_cc//cc:action_names.bzl", "C_COMPILE_ACTION_NAME")

def _compile_impl(ctx):
    args = [f.path for f in ctx.files.setup_files] + ["build_ext", "--inplace"]
    args.append("--libraries=" + ",".join([dep.basename.split(".so")[0][3:] for dep in ctx.files.deps if dep.basename.endswith(".so")]))
    args.append("--library-dirs=" + ",".join([dep.dirname for dep in ctx.files.deps if dep.basename.endswith(".so")]))

    # TODO: Use hermetic python
    ctx.actions.run_shell(
        outputs = [ctx.outputs.out],
        inputs = ctx.files.setup_files + ctx.files.input_files + ctx.files.deps,
        command = " ".join(["python3"] + args) +
                  ("; mv zprobe.cpython-310-x86_64-linux-gnu.so " + ctx.outputs.out.path),
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
