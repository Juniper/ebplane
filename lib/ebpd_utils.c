#include <linux/err.h>
#include <string.h>
#include "bpf/libbpf.h"
#include "lib/ebpd_utils.h"

int
ebpd_load_xdp_prog (const char *filepath, int ifindex, void **handle)
{
    struct bpf_object *obj = NULL;
    struct bpf_prog_load_attr load_attr = {
        .ifindex	= ifindex,
        .file           = filepath,
        .prog_type	= BPF_PROG_TYPE_XDP,
    };
    int ret, prog_fd = -1;

    ret = bpf_prog_load_xattr(&load_attr, &obj, &prog_fd);
    if (ret) {
        printf("Error loading file(%s) (%d): %s\n",
               filepath, ret, strerror(-ret));
        return -ret;
    }
    *handle = obj;
    printf("Successfully loaded bpf program\n");
    return 0;
}

int
ebpd_load_xdp_buffer (void *buf, int buf_size, const char *name, void **handle)
{
    struct bpf_object *obj = NULL;
    int ret;

    obj = bpf_object__open_buffer(buf, buf_size, name);
    if (IS_ERR_OR_NULL(obj)) {
        return PTR_ERR(obj);
    }
    printf("BPF buffer opened, obj: %p\n", obj);
    ret = bpf_object__load(obj);
    switch (ret) {
    case 0:
        *handle = obj;
        break;
    default:
        bpf_object__close(obj);
        break;
    }
    return ret;
}

void
ebpd_unload (void *handle)
{
    struct bpf_object *obj = (struct bpf_object *) handle;
    bpf_object__close(obj);
}

