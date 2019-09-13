#include "lib/ebpf/utils.h"
#include "uapi/linux/bpf.h"

__section("xdp")
int xdp_pass(struct xdp_md *ctx)
{
    return XDP_PASS;
}

