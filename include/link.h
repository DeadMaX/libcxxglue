#ifndef _LIBCXXGLUE_LINK_H_
#define _LIBCXXGLUE_LINK_H_

#include <cstddef>
#include <cstdint>

#define ElfW(x) libcxxglue::Elf_ ## x

namespace libcxxglue
{
	/* ELF base types. */
	using Elf_Addr = std::uintptr_t;
	using Elf_Off = std::ptrdiff_t;
	using Elf_SHalf = std::int16_t;
	using Elf_Half = std::uint16_t;
	using Elf_Sword = std::int32_t;
	using Elf_Word = std::uint32_t;
	using Elf_Xword = std::uint64_t;
	using Elf_Sxword = std::int64_t;

	struct elf32_phdr final
	{
		Elf_Word    p_type;
		Elf_Off     p_offset;
		Elf_Addr    p_vaddr;
		Elf_Addr    p_paddr;
		Elf_Word    p_filesz;
		Elf_Word    p_memsz;
		Elf_Word    p_flags;
		Elf_Word    p_align;
	};

	struct elf64_phdr final
       	{
		Elf_Word p_type;
		Elf_Word p_flags;
		Elf_Off p_offset;
		Elf_Addr p_vaddr;
		Elf_Addr p_paddr;
		Elf_Xword p_filesz;
		Elf_Xword p_memsz;
		Elf_Xword p_align;
	};

#if __LP64__
	using Elf_Phdr = elf64_phdr;
#else
	using Elf_Phdr = elf32_phdr;
#endif
}

/* Values for p_type. */
inline libcxxglue::Elf_Word PT_NULL =        0;       /* Unused entry. */
inline libcxxglue::Elf_Word PT_LOAD =        1;       /* Loadable segment. */
inline libcxxglue::Elf_Word PT_DYNAMIC =     2;       /* Dynamic linking information segment. */
inline libcxxglue::Elf_Word PT_INTERP =      3;       /* Pathname of interpreter. */
inline libcxxglue::Elf_Word PT_NOTE =        4;       /* Auxiliary information. */
inline libcxxglue::Elf_Word PT_SHLIB =       5;       /* Reserved (not used). */
inline libcxxglue::Elf_Word PT_PHDR =        6;       /* Location of program header itself. */
inline libcxxglue::Elf_Word PT_TLS =         7;       /* Thread local storage segment */
inline libcxxglue::Elf_Word PT_LOOS =        0x60000000;      /* First OS-specific. */
inline libcxxglue::Elf_Word PT_SUNW_UNWIND = 0x6464e550;      /* amd64 UNWIND program header */
inline libcxxglue::Elf_Word PT_GNU_EH_FRAME =0x6474e550;
inline libcxxglue::Elf_Word PT_GNU_STACK =   0x6474e551;
inline libcxxglue::Elf_Word PT_GNU_RELRO =   0x6474e552;
inline libcxxglue::Elf_Word PT_DUMP_DELTA =  0x6fb5d000;      /* va->pa map for kernel dumps
                                           (currently arm). */
inline libcxxglue::Elf_Word PT_LOSUNW =      0x6ffffffa;
inline libcxxglue::Elf_Word PT_SUNWBSS =     0x6ffffffa;      /* Sun Specific segment */
inline libcxxglue::Elf_Word PT_SUNWSTACK =   0x6ffffffb;      /* describes the stack segment */
inline libcxxglue::Elf_Word PT_SUNWDTRACE =  0x6ffffffc;      /* private */
inline libcxxglue::Elf_Word PT_SUNWCAP =     0x6ffffffd;      /* hard/soft capabilities segment */
inline libcxxglue::Elf_Word PT_HISUNW =      0x6fffffff;
inline libcxxglue::Elf_Word PT_HIOS =        0x6fffffff;      /* Last OS-specific. */
inline libcxxglue::Elf_Word PT_LOPROC =      0x70000000;      /* First processor-specific type. */
inline libcxxglue::Elf_Word PT_ARM_ARCHEXT = 0x70000000;      /* ARM arch compat information. */
inline libcxxglue::Elf_Word PT_ARM_EXIDX =   0x70000001;      /* ARM exception unwind tables. */
inline libcxxglue::Elf_Word PT_HIPROC =      0x7fffffff;      /* Last processor-specific type. */

struct dl_phdr_info final
{
	ElfW(Addr) dlpi_addr;
	const char *dlpi_name;
	const ElfW(Phdr) *dlpi_phdr;
	ElfW(Half) dlpi_phnum;

	__extension__ unsigned long long int dlpi_adds;
	__extension__ unsigned long long int dlpi_subs;

	std::size_t dlpi_tls_modid;

	void *dlpi_tls_data;

private:
	dl_phdr_info(const dl_phdr_info &) = delete;
	dl_phdr_info & operator=(const dl_phdr_info &) = delete;
	dl_phdr_info(dl_phdr_info &&) = delete;
	dl_phdr_info & operator=(dl_phdr_info &&) = delete;
};

typedef int (*__dl_iterate_hdr_callback)(dl_phdr_info *info, std::size_t Dl_info_size, void *arg);
int dl_iterate_phdr(__dl_iterate_hdr_callback cb, void *arg);

struct Dl_info final
{
        const char      *dli_fname;     /* Pathname of shared object. */
        void            *dli_fbase;     /* Base address of shared object. */
        const char      *dli_sname;     /* Name of nearest symbol. */
        void            *dli_saddr;     /* Address of nearest symbol. */

	Dl_info(){}
private:
	Dl_info(const Dl_info &) = delete;
	Dl_info & operator=(const Dl_info &) = delete;
	Dl_info(Dl_info &&) = delete;
	Dl_info & operator=(Dl_info &&) = delete;
};

int dladdr(const void * __restrict, Dl_info * __restrict);

#endif // _LIBCXXGLUE_LINK_H_

