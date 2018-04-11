#ifndef _LIBELF_LINK_H_
#define _LIBELF_LINK_H_

#include <cstddef>
#include <cstdint>

#define ElfW(x) libelf::Elf_ ## x

namespace libelf
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

#endif // _LIBELF_LINK_H_

