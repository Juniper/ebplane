#ifndef __XDP_LOADER_H_
#define __XDP_LOADER_H_

using namespace std;

class XdpLoader {
    public:
        XdpLoader(): handle(nullptr) { }
        ~XdpLoader();
        int LoadFrmFile(const string filepath, const int ifindex);
        int LoadFrmBuffer(const string_view buffer, const char *name);
    private:
        void *handle;
};

using XdpHandle = unique_ptr<XdpLoader>;

/*
 * API to load an xdp program into kernel
 * file path - path to the xdp object file
 * ifindex - ifindex to associate the program with
 */
XdpHandle LoadXdpFile(const string filepath, const int ifindex);
/*
 * API to load an xdp program from buffer into kernel
 * buffer - buffer containing xdp code
 * name (optional) - user given program name
 */
XdpHandle LoadXdpBuffer(const string_view buffer, const char *name);

#endif
