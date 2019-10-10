package(default_visibility = ["//lib:__subpackages__"])

load("//build:ebpf.bzl", "cc_ebpf")

cc_ebpf(
    name = "sample",
    srcs = ["sample.c"],
    hdrs = ["utils.h"],
    deps = ["@libbpf"],
)
