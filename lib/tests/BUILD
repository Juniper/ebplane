load("//build:embed.bzl", "cc_embed")
load("//build:ebpf.bzl", "cc_ebpf")

cc_ebpf(
  name = "ebpf_sample",
  srcs = ["testdata/ebpf_sample.c"],
  deps = ["@libbpf"],
)

cc_test(
    name = "ebpd_loader_test",
    srcs = ["ebpd_loader_test.cc"],
    deps = [
        "//lib:ebpd",
        "@gtest//:gtest_main",
        ":ebpf_sample",
    ]
)

