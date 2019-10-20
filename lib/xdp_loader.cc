#include <iostream>
#include <string>
#include <memory>
#include "lib/ebpd_utils.h"
#include "lib/ebpd.h"
#include "lib/xdp_loader.h"

int
XdpLoader::LoadFrmFile(const string filepath, const int ifindex) {
    int ret;
    ret = ebpd_load_xdp_prog(filepath.c_str(), ifindex, &handle);
    if (ret) {
        cout << "Error: eBPF program " << filepath << " load failed " << ret << "\n";
        return ret;
    }
    cout << "eBPF program load succeeded, obj: " << handle << "\n";
    return 0;
}

int
XdpLoader::LoadFrmBuffer(const string_view buffer, const char *name) {
    int ret;
    ret = ebpd_load_xdp_buffer((void *)buffer.data(), buffer.size(), name, &handle);
    if (ret) {
        cout << "Error: eBPF program " << name << " load failed " << ret << "\n";
        return ret;
    }
    cout << "eBPF buffer load succeeded, obj: " << handle << "\n";
    return 0;
}

XdpLoader::~XdpLoader() {
    if (handle) {
        ebpd_unload(handle);
        cout << "eBPF program unloaded, obj: " << handle << "\n";
    }
}

XdpHandle
LoadXdpFile(const string filepath, const int ifindex) {
    XdpHandle xdph(new XdpLoader());
    if (xdph->LoadFrmFile(filepath, ifindex) == 0) {
        return xdph;
    }
    return nullptr;
}

XdpHandle
LoadXdpBuffer(const string_view buffer, const char *name) {
    XdpHandle xdph(new XdpLoader());
    if (xdph->LoadFrmBuffer(buffer, name) == 0) {
        return xdph;
    }
    return nullptr;
}

