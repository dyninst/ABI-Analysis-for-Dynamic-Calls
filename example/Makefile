mylib.so:
	$(CXX) -Wall -Wextra -O0 -g -fPIC -shared mylib.cpp -o mylib.so

dlopen_test:
	$(CXX) -Wall -Wextra -O0 -g -fno-pie -no-pie -o dlopen_test dlopen_test.cpp -ldl

dlopen_analyzer_bpatch: mylib.so dlopen_test
	$(CXX) -I$(Dyninst_DIR)/include -L$(Dyninst_DIR)/lib -o dlopen_analyzer_bpatch dlopen_analyzer_bpatch.cpp -ldyninstAPI -lcommon

dlopen_analyzer_symtab: mylib.so dlopen_test
	$(CXX) -I$(Dyninst_DIR)/include -L$(Dyninst_DIR)/lib -o dlopen_analyzer_symtab dlopen_analyzer_symtab.cpp -lsymtabAPI -lcommon
	
dlopen_analyzer_parseapi: mylib.so dlopen_test
	$(CXX) -I$(Dyninst_DIR)/include -L$(Dyninst_DIR)/lib -o dlopen_analyzer_parseapi dlopen_analyzer_parseapi.cpp -lparseAPI -lcommon

.PHONY: all
all: mylib.so dlopen_test dlopen_analyzer_bpatch dlopen_analyzer_symtab dlopen_analyzer_parseapi
	
.PHONY: clean
clean:
	rm -rf dlopen_test dlopen_analyzer_bpatch dlopen_analyzer_symtab dlopen_analyzer_parseapi mylib.so
