#include <iostream>
#include <string>
#include "lib/ebpd_utils.h"
#include "lib/ebpd_loader.h"
#include "lib/ebpd.h"

using namespace std;

int
EbpdLoader::LoadFile(const char *filepath, int ifindex) {
    int ret;
    ret = ebpd_load_xdp_prog(filepath, ifindex, &handle);
    if (ret) {
        cout << "Error: eBPF program " << filepath << " load failed " << ret << "\n";
        return ret;
    }
    cout << "eBPF program load succeeded, obj: " << handle << "\n";
    return 0;
}

int
EbpdLoader::LoadBuffer(void *buf, int buf_size, const char *name) {
    int ret;
    ret = ebpd_load_xdp_buffer(buf, buf_size, name, &handle);
    if (ret) {
        cout << "Error: eBPF program " << name << " load failed " << ret << "\n";
        return ret;
    }
    cout << "eBPF buffer load succeeded, obj: " << handle << "\n";
    return 0;
}

EbpdLoader::~EbpdLoader() {
    if (handle) {
        ebpd_unload(handle);
        cout << "eBPF program unloaded, obj: " << handle << "\n";
    }
}

