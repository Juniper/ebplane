cc_binary(
    name = "ebpd",
    srcs = ["main.cc"],
    deps = [
	"//lib:ebpd"
    ],
)

cc_test(
    name = "main_test",
    srcs = ["main_test.cc"],
    deps = [
	"@gtest//:gtest_main",
	"//lib:ebpd"
    ],
)
