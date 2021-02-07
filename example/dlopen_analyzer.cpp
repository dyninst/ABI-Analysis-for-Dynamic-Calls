#include "BPatch.h"
#include "BPatch_function.h"
#include "BPatch_point.h"
#include <iomanip>

int main() {
  BPatch bpatch;
  BPatch_binaryEdit *appBin = bpatch.openBinary("dlopen_test");
  auto *image = appBin->getImage();

  std::vector<BPatch_function*> procs;
  image->getProcedures(procs);

  std::cout << "Found the following procedures: \n";
  for(auto *p : procs) { std::cout << '\t' << p->getName() << '\n'; }
  
  procs.clear();
  image->getProcedures(procs, true);
  std::cout << "Found the following procedures (including uninstrumentable ones): \n";
  for(auto *p : procs) { std::cout << '\t' << p->getName() << '\n'; }

  std::vector<BPatch_function *> found_funcs;
  image->findFunction("main", found_funcs);

  if(found_funcs.size() < 1) {
    std::cerr << "Did not find main\n";
    return -1;
  }

  std::cout << "findFunction found \n";
  for(auto *f : found_funcs) {
    std::cout << '\t' << f->getName() << '\n';
  }

  auto *calls = found_funcs[0]->findPoint(BPatch_locSubroutine);

  if(!calls) {
    std::cerr << "Found no calls\n";
    return -1;
  }

  std::cout << "findPoint found " << calls->size() << " calls\n";

//  This returns the same as findPoint(BPatch_locSubroutine)
//  std::vector<BPatch_point*> points;
//  found_funcs[0]->getCallPoints(points);

  for(auto *c : *calls) {
    BPatch_function *callee = c->getCalledFunction();
    if(callee) {
      std::cout << "Found callee " << callee->getName() << '\n';
    } else {
      std::cout << "Could not get callee at address " << std::hex << c->getAddress() << '\n';
    }
  }
}


/*
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

  // namespace st = Dyninst::SymtabAPI;

  // st::Symtab *obj = nullptr;
  // st::Symtab::openFile(obj, "dlopen_test");

  // std::vector<st::relocationEntry> entries;
  // obj->getFuncBindingTable(entries);

  // for(auto const& e : entries) {
  // std::cout << e << '\n';
  //}
}
*/
