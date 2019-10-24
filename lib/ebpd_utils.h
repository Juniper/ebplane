#ifndef LIB_EBPD_UTILS_H_
#define LIB_EBPD_UTILS_H_

#ifdef __cplusplus
extern "C"
{
#endif

/* Public utilities which can be used from userspace */

/*
 * API to load ebpf object code from a file into kernel
 */
extern int ebpd_load_xdp_prog (const char *filepath, int ifindex, void **handle);

/*
 * API to load ebpf object code from a buffer into kernel
 */
extern int ebpd_load_xdp_buffer (void *buf, int buf_size, const char *name, void **handle);

/*
 * API to unload a previously loaded bpf object
 */
extern void ebpd_unload (void *handle);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
