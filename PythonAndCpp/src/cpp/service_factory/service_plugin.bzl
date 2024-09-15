## Problematic TO BE FIX

def _compile_impl(ctx):
    target_lib = []
    target_lib_basename = []
    outputs_files = []
    plugin_folder = ctx.bin_dir.path.split(ctx.label.package)[0] + "/service_plugins/"
    for data in ctx.files.data:
        if data.basename.endswith(".so"):
            target_lib.append(data)
            target_lib_basename.append(data.basename)

    for i, plugin in enumerate(target_lib):
        plugin_file_name = plugin_folder + target_lib_basename[i]

        out_f = ctx.actions.declare_file(plugin_file_name)
        outputs_files.append(out_f)
        ctx.actions.run_shell(
            outputs = [out_f],
            inputs = depset([plugin]),
            arguments = [plugin_folder, plugin.path, plugin_file_name],
            command = "mkdir -p $1;cp $2 $3;echo $1 $2 $3",
        )

    return [
        DefaultInfo(
            files = depset(outputs_files),
            runfiles = ctx.runfiles(files = outputs_files),
        ),
    ]

service_plugin = rule(
    implementation = _compile_impl,
    attrs = {
        "data": attr.label_list(mandatory = True),
    },
)
