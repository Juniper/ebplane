load("//build:embed.bzl", "cc_embed")

cc_embed(
    name = "mediocrity",
    data = [":testdata/mediocrity.txt"]
)

cc_embed(
    name = "perseverance",
    data = [":testdata/perseverance.txt"]
)

# Embeds multiple files in one .h and library.
cc_embed(
    name = "multiple",
    data = [
      ":testdata/perseverance.txt",
      ":testdata/mediocrity.txt",
    ]
)

# Creates a library out of two separately embedded files,
# with individual .h files.
cc_library(
    name = "success",
    deps = [
      ":mediocrity",
      ":perseverance",
    ]
)

cc_library(
   name = "embed_test_lib",
   hdrs = ["embed_test.h"],
)

# Creates a library containing a string with a binary
# representation of another file.
cc_embed(
    name = "dependency",
    data = [":success"]
)

cc_test(
    name = "embed_test_simple",
    srcs = ["embed_test_simple.cc"],
    deps = [
        "@gtest//:gtest_main",
	":embed_test_lib",
        ":mediocrity",
    ]
)

cc_test(
    name = "embed_test_multiple",
    srcs = ["embed_test_multiple.cc"],
    deps = [
        "@gtest//:gtest_main",
	":embed_test_lib",
        ":multiple",
    ]
)

cc_test(
    name = "embed_test_library",
    srcs = ["embed_test_library.cc"],
    deps = [
        "@gtest//:gtest_main",
	":embed_test_lib",
        ":success",
    ]
)

cc_test(
    name = "embed_test_dependency",
    srcs = ["embed_test_dependency.cc"],
    deps = [
        "@gtest//:gtest_main",
        ":dependency",
    ]
)
