load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Change master to the git tag you want.
http_archive(
    name = "com_grail_bazel_toolchain",
    sha256 = "5ce22afa5b022adaf4644f2f5fc8727bc10c304f9f7539bd6ebda60569c9fd68",
    strip_prefix = "bazel-toolchain-master",
    urls = ["https://github.com/grailbio/bazel-toolchain/archive/master.tar.gz"],
)

load("@com_grail_bazel_toolchain//toolchain:rules.bzl", "llvm_toolchain")

llvm_toolchain(
    name = "llvm_toolchain",
    llvm_version = "8.0.0",
)

load("@llvm_toolchain//:toolchains.bzl", "llvm_register_toolchains")

llvm_register_toolchains()

