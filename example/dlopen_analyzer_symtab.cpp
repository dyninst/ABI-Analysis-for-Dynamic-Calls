#include <iostream>
#include "Symtab.h"
#include "Function.h"
#include "Module.h"

int main() {
  namespace st = Dyninst::SymtabAPI;

  st::Symtab *obj = nullptr;
  st::Symtab::openFile(obj, "dlopen_test");

  std::vector<st::Segment> segments;
  obj->getSegments(segments);

  for(auto const& s : segments) {
    std::cout << s.name << "\n";
  }
}
