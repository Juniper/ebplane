#ifndef LIB_XDP_LOADER_H_
#define LIB_XDP_LOADER_H_

class XdpLoader {
    public:
        XdpLoader() { };
        ~XdpLoader();
        int LoadFrmFile(const std::string& filepath, const int ifindex);
        int LoadFrmBuffer(const std::string_view& buffer, const std::string& name);
    private:
        void *handle_ = nullptr;
};

using XdpHandle = std::unique_ptr<XdpLoader>;

/*
 * API to load an xdp program into kernel
 * file path - path to the xdp object file
 * ifindex - ifindex to associate the program with
 */
XdpHandle LoadXdpFile(const std::string& filepath, const int ifindex);
/*
 * API to load an xdp program from buffer into kernel
 * buffer - buffer containing xdp code
 * name (optional) - user given program name
 */
XdpHandle LoadXdpBuffer(const std::string_view& buffer, const std::string& name);

#endif
