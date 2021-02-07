.PHONY: all
all:
	$(CXX) -Wall -Wextra -O0 -g -fPIC -shared mylib.cpp -o mylib.so
	$(CXX) -Wall -Wextra -O0 -g -fno-pie -no-pie -o dlopen_test dlopen_test.cpp -ldl
	$(CXX) -I$(Dyninst_DIR)/include -L$(Dyninst_DIR)/lib -o dlopen_analyzer dlopen_analyzer.cpp -ldyninstAPI -lsymtabAPI -lcommon -lparseAPI
	
.PHONY: clean
clean:
	rm -rf dlopen_test dlopen_analyzer mylib.so
