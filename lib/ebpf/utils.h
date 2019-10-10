#ifndef LIB_EBPF_UTILS_H_
#define LIB_EBPF_UTILS_H_

// ELF files organize code and data in named sections.
// eBPF ELF loaders use section names to load the parts of the file needed.
// The __section macro does two things: 
// - marks the symbol as being part of a specific section.
// - marks the symbol as being used, so it is not optimized out.
#define __section(NAME) __attribute__((section(NAME), used))

#endif
