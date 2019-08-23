#ifndef EBPD_PRIVATE_H_
#define EBPD_PRIVATE_H_

#include "include/uapi/linux/bpf.h"

#ifndef __section
#define __section(NAME)                  \
   __attribute__((section(NAME), used))
#endif

#endif
