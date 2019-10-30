cc_library(
    name = "posix",
    srcs = [
        "errno.cc",
    ],
    hdrs = [
        "close.h",
        "errno.h",
        "file_descriptor.h",
        "unique_file_descriptor.h",
    ],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//lib/base",
        "//lib/error",
    ],
)

cc_test(
    name = "errno_test",
    srcs = ["errno_test.cc"],
    deps = [
        "//lib/posix",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "unique_file_descriptor_test",
    srcs = [
        "unique_file_descriptor_test.cc",
    ],
    deps = [
        "//lib/posix",
        "@gtest//:gtest_main",
    ],
)
