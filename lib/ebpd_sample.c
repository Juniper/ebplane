#include "lib/ebpd.h"
#include "lib/ebpd_private.h"

__section("xdp")
int xdp_pass(struct xdp_md *ctx)
{
    return XDP_PASS;
}

