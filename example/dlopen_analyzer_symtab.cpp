#include <iostream>
#include <vector>
#include <string>
#include "Symtab.h"
#include "Function.h"
#include "Module.h"

std::vector<std::string> split(char const* data, int size) {
	std::vector<std::string> strs;
	std::string s;
	for(int i=0; i<size; i++) {
		if(data[i] == 0){
			strs.push_back(std::move(s));
		} else {
			s.push_back(data[i]);
		}
	}
	return strs;
}

int main() {
  namespace st = Dyninst::SymtabAPI;

  st::Symtab *obj = nullptr;
  st::Symtab::openFile(obj, "dlopen_test");

	/*
	 * This uses a simple heuristic of parsing the string table from the
	 * .rodata segment to see if there are any string literals in the
	 * binary that look like shared library names.
	 */
  std::vector<st::Segment> segments;
  obj->getSegments(segments);

  for(auto const& s : segments) {
		if(s.name != ".rodata") continue;
		std::cout << "Candidate libraries: \n";
		for(auto const& v : split(static_cast<char const*>(s.data), s.size)) {
			if(v.find(".so") != std::string::npos) {
				std::cout << "\t" << v << "\n";
			}
		}
  }
}
