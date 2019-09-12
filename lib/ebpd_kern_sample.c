#include "uapi/linux/bpf.h"

#ifndef __section
#define __section(NAME)                  \
   __attribute__((section(NAME), used))
#endif

__section("xdp")
int xdp_pass(struct xdp_md *ctx)
{
    return XDP_PASS;
}

