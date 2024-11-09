load("@rules_shell//shell:sh_binary.bzl", "sh_binary")

visibility("public")

def local_deploy_service_plugin(plugins_name, plugins):
    sh_binary(srcs = ["//src/cpp/service_deamon:deploy_plugins.sh"], name = plugins_name, data = plugins)
