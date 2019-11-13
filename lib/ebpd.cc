#include "lib/ebpd.h"
#include "lib/ebpd_utils.h"

#include <iostream>

int InitEbpdLib(void) {
    /* set the libbpf print function to ours */
    ebpd_override_libbpf_print_func();
    return 0;
}
