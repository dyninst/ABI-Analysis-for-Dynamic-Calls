#include "BPatch.h"
#include "BPatch_function.h"
#include "BPatch_point.h"
#include <iomanip>
#include <string>

int main(int argc, char *argv[]) {
  auto usage = [argv]() {
    std::cerr << "Usage: " << argv[0] << " [--open-deps]\n";
  };

  const bool open_dependencies = [argc, argv, &usage]() {
    if (argc > 2) {
      usage();
      exit(-1);
    }
    if (argc == 2) {
      if (argv[1] == std::string{"--open-deps"}) {
        return true;
      } else {
        usage();
        exit(-1);
      }
    }
    return false;
  }();

  BPatch bpatch;
  BPatch_binaryEdit *appBin =
      bpatch.openBinary("dlopen_test", open_dependencies);
  auto *image = appBin->getImage();

  std::vector<BPatch_function *> procs;
  image->getProcedures(procs);

  std::vector<BPatch_function *> found_funcs;
  image->findFunction("main", found_funcs);

  if (found_funcs.size() < 1) {
    std::cerr << "Did not find main\n";
    return -1;
  }

  std::cout << "findFunction found \n";
  for (auto *f : found_funcs) {
    std::cout << '\t' << f->getName() << '\n';
  }

  auto *calls = found_funcs[0]->findPoint(BPatch_locSubroutine);

  if (!calls) {
    std::cerr << "Found no calls\n";
    return -1;
  }

  std::cout << "findPoint found " << calls->size() << " calls\n";

  for (auto *c : *calls) {
    BPatch_function *callee = c->getCalledFunction();
    if (callee) {
      // std::cout << "Parameters for callee " << callee->getName() << '\n';
      // for(auto *p : *callee->getVars()) {
      // std::cout << "\t" << p->getName() << " : " << p->getType()->getName()
      // << '\n';
      //}
    } else {
      std::cout << "Could not get callee at address " << std::hex
                << c->getAddress() << '\n';
    }
  }
}
