load("@rules_shell//shell:sh_binary.bzl", "sh_binary")

visibility("public")

def local_deploy_service_plugin(plugins_name, plugins):
    sh_binary(srcs = ["@z_python_cpp//exports/shell:deploy_plugins.sh"], name = plugins_name, data = plugins)
