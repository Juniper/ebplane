cc_library(
    name = "ebpd",
    srcs = ["ebpd.cc"],
    hdrs = ["ebpd.h"],
    deps = [
        "//lib/ebpf:sample",
    ],
    visibility = [
        "//visibility:public"
    ],
)

cc_library(
    name = "error",
    srcs = ["status.cc"],
    hdrs = [
        "invariant.h",
        "status.h",
    ],
)

cc_test(
    name = "status_test",
    srcs = ["status_test.cc"],
    deps = [
	"@gtest//:gtest_main",
	"//lib:error"
    ],
)
