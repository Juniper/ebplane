# Library of error handling utilities.
# With very limited exceptions, any function that can encounter complex error
# should use this library to report errors to the caller.
cc_library(
    name = "error",
    hdrs = [
        "assign_or_return.h",
        "code.h",
        "return_if_error.h",
        "status.h",
        "status_or.h",
    ],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//lib/base",
    ],
)

cc_test(
    name = "code_test",
    srcs = ["code_test.cc"],
    deps = [
        "//lib/error",
        "//lib/posix",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "status_test",
    srcs = ["status_test.cc"],
    deps = [
        "//lib/error",
        "//lib/posix",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "status_or_test",
    srcs = ["status_or_test.cc"],
    deps = [
        "//lib/error",
        "//lib/posix",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "return_if_error_test",
    srcs = ["return_if_error_test.cc"],
    deps = [
        "//lib/error",
        "//lib/posix",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "assign_or_return_test",
    srcs = ["assign_or_return_test.cc"],
    deps = [
        "//lib/error",
        "//lib/posix",
        "@gtest//:gtest_main",
    ],
)
