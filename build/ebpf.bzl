"""Provides ability to build and embed eBPF bytecode in C/C++ binaries.

The kernel interface for eBPF pretty much requires ELF object files
compiled for the eBPF platform - containing eBPF bytecode.
The ELF object files are passed as a string to the syscall, copied
in kernel space, and executed by the eBPF VM.

This file defines two rules:

- cc_build_ebpf - that simply compiles a .c file into a .pic.o file
  containing eBPF bytecode.

- cc_ebpf - that uses cc_build_ebpf and cc_embed to actually make the
  eBPF bytecode available as a std::string_view into a cpp file.

See the documentation for each rule and the examples under tests/ for
more details.
"""

load("@bazel_tools//tools/cpp:toolchain_utils.bzl", "find_cpp_toolchain")
load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "C_COMPILE_ACTION_NAME")
load("//build:embed.bzl", "cc_embed")

def _cc_build_ebpf(ctx):
  cc_toolchain = find_cpp_toolchain(ctx)

  # cc_common is the sklark library used to access C/C++ build primitives
  # in bazel, more details here:
  #   https://docs.bazel.build/versions/master/skylark/lib/cc_common.html
  feature_configuration = cc_common.configure_features(
     ctx = ctx,
     cc_toolchain = cc_toolchain,
     requested_features = ctx.features,
     unsupported_features = ctx.disabled_features,
  )
  compilation_contexts = []
  linking_contexts = []
  for dep in ctx.attr.deps:
    if not CcInfo in dep:
      fail("All dependencies must be C or C++ targets - exporting CcInfo") 

    compilation_contexts.append(dep[CcInfo].compilation_context)
    linking_contexts.append(dep[CcInfo].linking_context)

  # TODO: some of the options here are technically wrong: they use the
  # default toolchain provided by bazel, and just add flags on top of the
  # default options. But the default options might not work here, a dedicated
  # toolchain is required, will be submitted in a separate PR.
  compilation_context, compilation_outputs = cc_common.compile(
      name = ctx.label.name,
      actions = ctx.actions,
      feature_configuration = feature_configuration,
      cc_toolchain = cc_toolchain,
      public_hdrs = ctx.files.hdrs,
      srcs = ctx.files.srcs,
      includes = ctx.attr.includes,
      defines = ctx.attr.defines,
      user_compile_flags = ["--target=bpf"] + ctx.attr.copts,
      compilation_contexts = compilation_contexts,
  )

  # The bpf code has been compiled by the toolchain, so why not return CcInfo?
  # BPF code cannot really be linked together (not supported) and there's not
  # much we can do with it beside... loading it.
  # Using DefaultInfo guarantees it is treated as a blob of bytes by the rest
  # of bazel. We should consider returning a CcInfo if this ever changes.
  return [
      DefaultInfo(files = depset(items = compilation_outputs.pic_objects)),
  ]

cc_build_ebpf = rule(
  implementation = _cc_build_ebpf,
  attrs = {
       "srcs": attr.label_list(
           allow_files = [".c"],
           mandatory = True,
           doc = "File containing the C code to turn into an eBPF target."
       ),
       "deps": attr.label_list(
           doc = "Other dependencies of the target."
       ),
       "hdrs": attr.label_list(
           allow_files = [".h"],
           doc = "Header files part of the target."
       ),
       "includes": attr.string_list(
           doc = "Additional include paths for headers."
       ),
       "defines": attr.string_list(
           doc = "Defines passed to compiler for target and dependencies. "
               + "Similar to using -D <string> with the compiler."
       ),
       "copts": attr.string_list(
           doc = "Additional options passed to the compiler."
       ),
       "_cc_toolchain": attr.label(
           default = Label("@bazel_tools//tools/cpp:current_cc_toolchain")
       ),
  },
  toolchains = ["@bazel_tools//tools/cpp:toolchain_type"],
  fragments = ["cpp"],
  doc = """
Compiles .c code into eBPF bytecode.

Example:
  cc_build_ebpf(
    name = "sample",
    srcs = ["sample.c"]
  )

Will result in a "sample.pic.o" being generated containing
the eBPF bytecode compiled off sample.c.
""",
)

def cc_ebpf(name, **kwargs):
  """Compiles C code into eBPF, and embeds it into an object file.

  Use this macro to create eBPF bytecode and have it available from your
  code as a simple std::string_view.

  Internally, this macro generates a cc_build_ebpf() target, and a
  cc_embed target using it.

  Args:
    **kwargs: parameters are passed unchanged to cc_build_ebpf.
  """
  cc_build_ebpf(name = name + "-built-ebpf", **kwargs)
  cc_embed(name = name, namespace = "ebpf", data = [":" + name + "-built-ebpf"])
