load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "rules_foreign_cc",
    strip_prefix = "rules_foreign_cc-c3d5405cbc570257e7c9f75f902fab42241e6a53",
    url = "https://github.com/bazelbuild/rules_foreign_cc/archive/c3d5405.zip",
    sha256 = "b30d354592980848dd1ecc120de3de34a7c574985e85b3ae2bcecd174fd007b8",
)

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies()

http_archive(
    name = "elfutils",
    url = "https://sourceware.org/elfutils/ftp/0.177/elfutils-0.177.tar.bz2",
    sha256 = "fa489deccbcae7d8c920f60d85906124c1989c591196d90e0fd668e3dc05042e",
    strip_prefix = "elfutils-0.177",
    build_file = "//third_party:BUILD.elf",
)

http_archive(
    name = "libbpf",
    url = "https://github.com/libbpf/libbpf/archive/v0.0.4.zip",
    sha256 = "c89ca0958674e1efcfec5f92554b4596a592ee637d18657302382f7e57ddbea6",
    strip_prefix = "libbpf-0.0.4",
    build_file = "//third_party:BUILD.bpf",
)

http_archive(
    name = "gtest",
    url = "https://github.com/google/googletest/archive/release-1.8.1.zip",
    sha256 = "927827c183d01734cc5cfef85e0ff3f5a92ffe6188e0d18e909c5efebf28a0c7",
    strip_prefix = "googletest-release-1.8.1",
)

#
# Download the longterm stable kernel version in 4.1x series at the time of
# writing this;
# NOTE: This is a moving target
http_archive(
    name = "linuxsrc",
    url = "https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.15.18.tar.gz",
    sha256 = "ca13fa5c6e3a6b434556530d92bc1fc86532c2f4f5ae0ed766f6b709322d6495",
    strip_prefix = "linux-4.15.18",
    build_file = "//third_party:BUILD.install_linux_hdr",
)

#############################################################################
# All rules below are to configure the bazel remote build environment, and bring
# in clang-8 based toolchains on your system automatically.
# 
# More details are here: https://github.com/bazelbuild/bazel-toolchains/

# Change master to the git tag you want.
http_archive(
    name = "com_grail_bazel_toolchain",
    # TODO: update url and sha256 prefix to use a tag - rather than an explicit commit - as soon as
    # there is a toolchain release that includes Marcus' fix
    #     https://github.com/grailbio/bazel-toolchain/commit/f6b6ec8e1398f7163e6bf21599d3c58ad74a5966
    sha256 = "90e34dbd97e27fa2a0229bff5e1e3d3e56db8c93d64ddb15e3ba7d787c497898",
    strip_prefix = "bazel-toolchain-f6b6ec8e1398f7163e6bf21599d3c58ad74a5966",
    urls = ["https://github.com/grailbio/bazel-toolchain/archive/f6b6ec8.tar.gz"],
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

http_archive(
    name = "bazel_toolchains",
    sha256 = "388da5cc148a43081c30c260ce1167747d8fb0968ee220e4ee1d1b1b8212eaa3",
    strip_prefix = "bazel-toolchains-0.29.9",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-toolchains/archive/0.29.9.tar.gz",
        "https://github.com/bazelbuild/bazel-toolchains/archive/0.29.9.tar.gz",
    ],
)

load("@bazel_toolchains//rules:rbe_repo.bzl", "rbe_autoconfig")

# Creates a default toolchain config for RBE.
# Use this as is if you are using the rbe_ubuntu16_04 container,
# otherwise refer to RBE docs.
rbe_autoconfig(name = "rbe_default")

