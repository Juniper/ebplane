#ifndef __EBPD_LOADER_H_
#define __EBPD_LOADER_H_

class EbpdLoader {
    public:
        EbpdLoader() { }
        ~EbpdLoader();
        int LoadFile(const char *filepath, int ifindex);
        int LoadBuffer(void *buf, int buf_size, const char *name);
    private:
        void *handle;
};

#endif
