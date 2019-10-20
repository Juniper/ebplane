load("//build:embed.bzl", "cc_embed")
load("//build:ebpf.bzl", "cc_ebpf")

cc_test(
    name = "xdp_loader_test",
    srcs = ["xdp_loader_test.cc"],
    deps = [
        "//lib:ebpd",
        "@gtest//:gtest_main",
        "//lib/ebpf:sample",
    ]
)

