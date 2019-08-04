load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Change master to the git tag you want.
http_archive(
    name = "com_grail_bazel_toolchain",
    sha256 = "c9ccd54cb7a1a0425717946c6a202bfdc17af1e759a7bdcf288779e9328c8085",
    strip_prefix = "bazel-toolchain-master",
    urls = ["https://github.com/h-fam/bazel-toolchain/archive/master.tar.gz"],
)

load("@com_grail_bazel_toolchain//toolchain:rules.bzl", "llvm_toolchain")

llvm_toolchain(
    name = "llvm_toolchain",
    llvm_version = "8.0.0",
)

load("@llvm_toolchain//:toolchains.bzl", "llvm_register_toolchains")

llvm_register_toolchains()

