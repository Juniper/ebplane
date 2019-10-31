cc_library(
    name = "bpf",
    hdrs = [
        "bpf.h",
        "map_create.h",
        "map_lookup_element.h",
        "map_update_element.h",
        "prog_load.h",
    ],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//lib/base",
        "//lib/posix",
    ],
)

cc_test(
    name = "bpf_test",
    srcs = ["bpf_test.cc"],
    deps = [
        "//lib/bpf",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "prog_load_test",
    srcs = ["prog_load_test.cc"],
    deps = [
        "//lib/bpf",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "map_test",
    srcs = ["map_test.cc"],
    deps = [
        "//lib/bpf",
        "@gtest//:gtest_main",
    ],
)
