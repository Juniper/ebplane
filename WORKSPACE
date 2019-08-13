load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "gtest",
    url = "https://github.com/google/googletest/archive/release-1.8.1.zip",
    sha256 = "927827c183d01734cc5cfef85e0ff3f5a92ffe6188e0d18e909c5efebf28a0c7",
    strip_prefix = "googletest-release-1.8.1",
)

#############################################################################
# All rules below are to configure the bazel remote build environment, and bring
# in clang-8 based toolchains on your system automatically.
# 
# More details are here: https://github.com/bazelbuild/bazel-toolchains/

# Change master to the git tag you want.
http_archive(
    name = "com_grail_bazel_toolchain",
    # TODO: update url and sha256 prefix as soon as there is a toolchain release that includes Marcus'
    # fix https://github.com/grailbio/bazel-toolchain/commit/f6b6ec8e1398f7163e6bf21599d3c58ad74a5966
    sha256 = "dbd4af742495c507232bdc0df8dcea66867ea662ecfe3c802eb4a613ea5d8a4b",
    strip_prefix = "bazel-toolchain-f6b6ec8e1398f7163e6bf21599d3c58ad74a5966",
    urls = ["https://github.com/grailbio/bazel-toolchain/archive/f6b6ec8e1398f7163e6bf21599d3c58ad74a5966.zip"],
)

load("@com_grail_bazel_toolchain//toolchain:rules.bzl", "llvm_toolchain")

llvm_toolchain(
    name = "llvm_toolchain",
    distribution = "auto",
    #distribution = "clang+llvm-8.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz",
    llvm_version = "8.0.0",
)

load("@llvm_toolchain//:toolchains.bzl", "llvm_register_toolchains")

llvm_register_toolchains()
