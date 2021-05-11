#include <elfutils/libdw.h>
#include <elfutils/libdwfl.h>
#include <stdio.h>
#include <stdlib.h>

static const Dwfl_Callbacks dwfl_callbacks =
{
    dwfl_build_id_find_elf,
    dwfl_standard_find_debuginfo,
    dwfl_offline_section_address,
    NULL
};

int main(int argc, char* argv[]) {
  if(argc != 2) {
		fprintf(stderr, "Usage: %s file\n", argv[0]);
		exit(-1);
	}
  
	Dwfl *dwfl = dwfl_begin(&dwfl_callbacks);
	dwfl_report_begin(dwfl);
	Dwfl_Module *mod = dwfl_report_elf(dwfl, argv[1], argv[1], -1, 0, 1);
	dwfl_report_end(dwfl, NULL, NULL);

	Dwarf_Addr bias;

  Elf *elf = dwfl_module_getelf(mod, &bias);
  GElf_Ehdr ehdr_mem;
  GElf_Ehdr *ehdr = gelf_getehdr(elf, &ehdr_mem);
  if(!ehdr) goto done;
  
  printf(
		"Elf Header:\n"
		"\ttype: %d\n"
		"\tmachine: %d\n"
		"\tversion: %d\n"
		"\tProgram Header Count: %d\n"
		"\tSection Header Count: %d\n"
		"\tString Table Index: %d\n",
		(int)ehdr->e_type,
		(int)ehdr->e_machine,
		(int)ehdr->e_version,
		(int)ehdr->e_phnum,
		(int)ehdr->e_shnum,
		(int)ehdr->e_shstrndx
	);

//	Dwarf* file_data = dwfl_module_getdwarf(mod, &bias);

done:
  dwfl_end(dwfl);  
}
