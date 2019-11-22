#include "lib/ebpf/utils.h"
#include "uapi/linux/bpf.h"

/* kernel version from /usr/include/linux/version.h */
__section("version")
__u32 kver = 263349;

__section("xdp")
int xdp_pass(struct xdp_md *ctx)
{
    return XDP_PASS;
}

__section("license")
char _license[] = "GPL";

