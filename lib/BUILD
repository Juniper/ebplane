exports_files(["someData.txt"])

cc_library(
    name = "ebpd",
    srcs = ["ebpd.cc"],
    hdrs = ["ebpd.h"],
    visibility = [
        "//visibility:public"
    ],
)

#
# Enable this rule and execute "bazel build //lib:ebpd_kern_sample
# to generate ebpd_kern_sample.pic.o; ebpd_kern_sample.pic.o can
# be loaded into kernel using ip link set command
#
# TODO: Fix the linker error as the .o generated is in bpf target arch
#       but ld.lld expects x86_64
#
#cc_library(
#    name = "ebpd_kern",
#    srcs = ["ebpd_kern_sample.c"],
#    copts = [ "--target=bpf",
#              "-Iexternal/libbpf/include" ],
#    deps = ["@libbpf"],
#    visibility = [
#        "//visibility:public"
#    ],
#)
