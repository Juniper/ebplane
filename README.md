# ebplane - an eBPF based dataplane

This repository contains prototypes of an eBPF based dataplane for network applications,
its supporting libraries, tools, and documentation.

# Working on ebplane

To work on ebplane, you must:

1) Install bazel, by following the [instructions here](https://docs.bazel.build/versions/master/install.html).

2) Build all the binaries, by running:

        bazel build ...:all

3) Run the tests, by running:

        bazel test ...:all

Binaries can then be found in the `bazel-bin` directory.

The build environment transparently downloads and uses a default toolchain.
Your system does not need compiler, linker or header files installed.

However, if you receive a python stack trace with the error:

    Failed to detect host OS version: [...]

It means there is no pre-built environment for your platform.
We recommend you send a PR to update:

    https://github.com/grailbio/bazel-toolchain/blob/master/toolchain/tools/llvm_release_name.py#L34

and/or pass `TODO` flag to use a local clang install.


# Developing ebplane

1) All code checked in must have corresponding tests.

2) Make sure your code is formatted properly with `clang-format`, by running:

        TODO

3) Verify no new warnings via static analysis:

        TODO

4) Verify that all tests are passing:

        bazel test ...:all
        bazel test --config=msan ...:all # Uses memory sanitizer.
        bazel test --config=tsan ...:all # Uses thread sanitizer.
        bazel test --config=asan ...:all # Uses address sanitizer.
        bazel test --config=ubsan ...:all # Uses the undefined behavior sanitizer.

5) Send code for review.
