# Library of error handling utilities.
# With very limited exceptions, any function that can encounter complex error
# should use this library to report errors to the caller.
cc_library(
    name = "error",
    hdrs = [
        "status.h",
        "status_or.h",
        "return_if_error.h",
        "assign_or_return.h",
    ],
    deps = [
        "//lib/base",
    ],
    visibility = [
        "//visibility:public"
    ],
)

cc_test(
    name = "status_test",
    srcs = ["status_test.cc"],
    deps = [
	"@gtest//:gtest_main",
	"//lib/error"
    ],
)

cc_test(
    name = "status_or_test",
    srcs = ["status_or_test.cc"],
    deps = [
	"@gtest//:gtest_main",
	"//lib/error"
    ],
)

cc_test(
    name = "return_if_error_test",
    srcs = ["return_if_error_test.cc"],
    deps = [
	"@gtest//:gtest_main",
	"//lib/error"
    ],
)

cc_test(
    name = "assign_or_return_test",
    srcs = ["assign_or_return_test.cc"],
    deps = [
	"@gtest//:gtest_main",
	"//lib/error"
    ],
)