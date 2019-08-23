exports_files(["someData.txt"])

cc_library(
    name = "ebpd",
    srcs = ["ebpd_sample.c",
            "ebpd_private.h"],
    hdrs = ["ebpd.h"],
    copts = ["--target=bpf"],
    deps = ["@libbpf"],
    visibility = [
        "//visibility:public"
    ],
)
