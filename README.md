# ebplane - an eBPF based dataplane

This repository contains prototypes of an eBPF based dataplane for network applications,
its supporting libraries, tools, and documentation.

# Working on ebplane

## Install development tools locally
To work on ebplane, you must:

1) Install bazel, by following the [instructions here](https://docs.bazel.build/versions/master/install.html). 
Make sure you install version [0.29.1](https://github.com/bazelbuild/bazel/releases/tag/0.29.1), 
newer versions do not yet work.

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

If you see the following error while building:

   /usr/include/stdint.h:26:10: fatal error: 'bits/libc-header-start.h' file not found

On Ubuntu this can be resolved by installing:

   apt install gcc-multilib g++-multilib


## Docker build container

Instead of installing the build tools locally you could also use a docker 
container that will install all the required tools. For more details see the
[README.md](docker/README.md) in the docker folder.


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
