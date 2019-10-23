# Library of simple header only utilities.
# Good candidates for functions in 'base':
#  * Don't do I/O
#  * Don't handle complex errors
#  * Work well in a header only library
#
# Examples include:
#  * Trivial math
#  * Type utilities
#  * Simple macros
#  * Generic code with no dependencies
#
# base should NEVER have non-empty 'deps' or 'srcs'
cc_library(
    name = "base",
    hdrs = [
        "invariant.h",
        "opaque_value.h",
    ],
    visibility = [
        "//visibility:public"
    ],
)

cc_test(
    name = "opaque_value_test",
    srcs = ["opaque_value_test.cc"],
    deps = [
	"@gtest//:gtest_main",
	"//lib/base"
    ],
)
