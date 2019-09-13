"""Provides ability to embed assets in C++ libraries and binaries.

Use the rules in this bazel files by configuring your BUILD with:

  load("//build/embed.bzl", "cc_embed")
  ...

  cc_embed(
    name = "targetname",
    data = [
      ":file.txt",
      ":file.jpeg",
      ":othertarget",
      "//another/target",
    ]
  )

  # Can either be cc_binary or cc_library.
  cc_binary(
    ...
    deps = [
      ":targetname",
      ...
    ]
  )

This will result in:
  1) A "targetname" C++ library being created, linkable like any other library.
  2) "file.txt", "file.jpeg", the results of building ":othertarget"
     and "//another/target" being linked directly into this library.
  3) A "targetname.h" file being created, defining std::string_view objects
     containing the raw bytes of the specified files. In the example, it
     would define: "embedded::file_txt" and "embedded::file_jpeg".
  4) The name of the indirect target will depend on what that target is.
     Most likely, it will contain the file exported by the target
     (eg, "embedded::othertarget_a" if "othertarget" is a cc_library).

Using embedded files is extremely easy, this is what your .cc file will look
like:

    #include "targetname.h"
    
    void test() {
      std::cout << embedded::file_txt << std::endl;
    }

See the tests/ directory for more details.
"""

load("@bazel_tools//tools/cpp:toolchain_utils.bzl", "find_cpp_toolchain")
load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "CPP_LINK_STATIC_LIBRARY_ACTION_NAME")
load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "C_COMPILE_ACTION_NAME")

def _clean_path(directory):
   """Turns a bazel-out/whatever/bin/base/dir into base/dir.
   
   Args:
     directory: string, the path to clean.

   Returns:
     The cleaned path, or the original path if the cleaning pattern
     cannot be found.
   """
   parts = directory.split("/bin/", 1)
   if len(parts) > 1:
     return _clean_string(parts[1])
   return _clean_string(parts[0])

def _clean_string(s):
   """Replaces invalid characters with _.

   This is used to turn filenames (or strings in general) into valid
   variable names. It losely emulates the behavior of "ld".

   Args:
     s: string, path of a file to clean.

   Returns:
     The cleaned string, with invalid characters replaced.
   """
   # TODO: it would be better to say s/[^a-zA-Z0-9]/_/g, but starlark
   #   does not support regexes, or python APIs that would allow this.
   #   Recommended solution would be to build and use a tool.
   #   Much more work. Fix it if we ever get paths with invalid characters.
   return s.replace("/", "_").replace(".", "_").replace("-", "_").replace(" ", "_").replace("[", "_").replace("]", "_")

def _cc_embed(ctx):
    cc_toolchain = find_cpp_toolchain(ctx)

    ### Step 1: Determine the input files to add to the .o file.
    libinputs = []
    for input in ctx.attr.data:
      # Bazel dependencies can attach arbitrary metadata to a rule via
      # providers. Check if the dependency is a cc_.* "thing", having
      # the CcInfo provider. If it is a Cc thing, embed the generated
      # object files that best work for us.
      if CcInfo not in input:
        continue
      info = input[CcInfo]
      if not info.linking_context:
        continue
      for lib in info.linking_context.libraries_to_link.to_list():
        if lib.pic_static_library:
          libinputs.append(lib.pic_static_library)
        elif lib.static_library:  
          libinputs.append(lib.static_library)
        elif lib.interface_library:  
          libinputs.append(lib.interface_library)
        elif lib.dynamic_library:  
          libinputs.append(lib.interface_library)
    inputs = depset(direct=libinputs, transitive=[target.files for target in ctx.attr.data])

    objfile = ctx.actions.declare_file(ctx.label.name + ".o")

    # TODO: ld_executable API is deprecated in theory, but there is no replacement yet.
    # See https://github.com/bazelbuild/bazel/issues/8802.
    linker = cc_toolchain.ld_executable

    # The linker command line changes between clang and gcc.
    # Further, the elf_amd64 string should be computed from the actual platform
    # used, not hard coded.
    # TODO: as multi toolchain support is added, use the gcc linker - which
    #       should create the correct object format out of the box.
    args = ctx.actions.args()
    args.add_all(inputs)
    ctx.actions.run(
        executable = linker,
        progress_message = "Magically embedding %s into %s" % ([i.path for i in inputs.to_list()], objfile.path),
        arguments = ["-r", "-b", "binary", "-m", "elf_amd64", args, "-o", objfile.path],
        inputs = depset(
            items = inputs.to_list(), 
            transitive = [cc_toolchain.all_files],
        ),
        outputs = [objfile],
    )

    ### Step 2: generate .h file with the variables needed.
    hfile = ctx.actions.declare_file(ctx.label.name + ".h")
    symbols = []
    accessors = []
    for i in inputs.to_list():
      clean = _clean_string(i.path)
      subs = {
        "start": "_binary_{}_start".format(clean),
        "end": "_binary_{}_end".format(clean),
        "var": _clean_string(i.path.split("/")[-1]),
      }

      symbols.append("extern const char {start};".format(**subs))
      symbols.append("extern const char {end};".format(**subs))
      accessors.append("inline const std::string_view {var}(&{start}, &{end} - &{start});".format(**subs))

    ifguard = _clean_path(hfile.path).upper()
    ctx.actions.expand_template(
      template = ctx.file._template,
      output = hfile,
      substitutions = {
        "IFGUARD": ifguard,
        "SYMBOLS": "\n".join(symbols),
        "ACCESSORS": "\n".join(accessors),
      }
    ) 

    ### Step 3: create .a static library - required for linking.
    arfile = ctx.actions.declare_file(ctx.label.name + ".a")
    feature_configuration = cc_common.configure_features(
        ctx = ctx,
        cc_toolchain = cc_toolchain,
        requested_features = ctx.features,
        unsupported_features = ctx.disabled_features,
    )

    archiver_path = cc_common.get_tool_for_action(
        feature_configuration = feature_configuration,
        action_name = CPP_LINK_STATIC_LIBRARY_ACTION_NAME,
    )   
    archiver_variables = cc_common.create_link_variables(
        feature_configuration = feature_configuration,
        cc_toolchain = cc_toolchain,
        output_file = arfile.path,
        is_using_linker = False,
    )   
    command_line = cc_common.get_memory_inefficient_command_line(
        feature_configuration = feature_configuration,
        action_name = CPP_LINK_STATIC_LIBRARY_ACTION_NAME,
        variables = archiver_variables,
    )   

    args = ctx.actions.args()
    args.add_all(command_line)
    args.add(objfile)
    
    env = cc_common.get_environment_variables(
        feature_configuration = feature_configuration,
        action_name = CPP_LINK_STATIC_LIBRARY_ACTION_NAME,
        variables = archiver_variables,
    )

    ctx.actions.run(
        executable = archiver_path,
        arguments = [args],
        env = env,
        progress_message = "Turning %s into library %s" % (objfile.path, arfile.path),
        inputs = depset(
            direct = [objfile],
            transitive = [
                cc_toolchain.all_files,
            ],  
        ),  
        outputs = [arfile],
    )   

    ### Step 4: return the generated files for the caller to use.
    library_to_link = cc_common.create_library_to_link(
        actions = ctx.actions,
        feature_configuration = feature_configuration,
        cc_toolchain = cc_toolchain,
        static_library = arfile,
    )
    compilation_context = cc_common.create_compilation_context(
        includes = depset([hfile.dirname]),
        headers = depset([hfile])
    )
    linking_context = cc_common.create_linking_context(libraries_to_link = [library_to_link])

    return [
        DefaultInfo(files = depset([hfile])),
        CcInfo(compilation_context = compilation_context, linking_context = linking_context),
    ]

cc_embed = rule(
  implementation = _cc_embed,
  attrs = {
       "data" : attr.label_list(
           allow_files = True,
           mandatory = True,
           doc = "Targets to turn into strings and embed in the binary."
       ),
       "_template": attr.label(
           default = Label("//build:embed.h.tpl"),
           allow_single_file = True,
       ),
       "_cc_toolchain": attr.label(
           default = Label("@bazel_tools//tools/cpp:current_cc_toolchain")
       ),
  },
  toolchains = ["@bazel_tools//tools/cpp:toolchain_type"],
  fragments = ["cpp"],
  doc = """
Creates a library with the specified data dependencies as string.

Example:

  cc_embed(
    name = "targetname",
    data = [
      ":file.txt",
    ]
  )

Will result in:
  1) A "targetname" library created, and linkable from the deps
     of other cc_binary or library rules.
  2) A "targetname.h" created, containing a std::string_view
     named "embedded::file_txt" with the raw content of the file.

The rule uses magic compiler tricks to get the file into an object
file directly.
""",
)
