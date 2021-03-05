#include "CodeObject.h"
#include "CodeSource.h"

int main() {
  using namespace Dyninst::ParseAPI;
  char const *binary_name = "dlopen_test";
  SymtabCodeSource *sts = new SymtabCodeSource(const_cast<char *>(binary_name));
  CodeObject *co = new CodeObject(sts);
  co->parse();

  for (auto *f : co->funcs()) {
    if (f->name() == "dlopen") {
      auto *block = f->entry();
      for (auto *edge : block->sources()) {
        Block *src = edge->src();

        // TODO:
        //  use Block::getInsns to find registers used for call arguments
        //  Use Symtab to find types and names of parameters
      }
    }
  }
}
