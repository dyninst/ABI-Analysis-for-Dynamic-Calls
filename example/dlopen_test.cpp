#include <dlfcn.h>
#include <cstdio>

int foo() {
  return printf("Hello");
}

int main() {
	void *handle = dlopen("mylib.so", RTLD_LAZY);
	if(!handle) {
		fprintf(stderr, "dlopen failed: %s\n", dlerror());
		return -1;
	}

	foo();
	
	void *func = dlsym(handle, "hello");
	if(func) {
		reinterpret_cast<void(*)()>(func)();
	}
	
	dlclose(handle);
}
