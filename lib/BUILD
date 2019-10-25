cc_library(
    name = "ebpd",
    srcs = ["ebpd.cc",
            "ebpd_utils.c",
            "xdp_loader.cc",
            ],
    hdrs = ["ebpd.h",
            "ebpd_utils.h",
            "xdp_loader.h",
           ],
    copts = ["-Iexternal/libbpf/include", ],
    deps = [
        "//lib/ebpf:sample",
        "@libbpf",
    ],
    visibility = [
        "//visibility:public"
    ],
)

