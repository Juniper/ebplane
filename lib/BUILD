cc_library(
    name = "ebpd",
    srcs = ["ebpd.cc",
            "ebpd_loader.cc",
            "ebpd_utils.c",
            ],
    hdrs = ["ebpd.h",
            "ebpd_loader.h",
            "ebpd_utils.h"
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

