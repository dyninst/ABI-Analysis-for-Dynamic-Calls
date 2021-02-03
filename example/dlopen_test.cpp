#include <dlfcn.h>
#include <cstdio>

int main() {
	void *handle = dlopen("mylib.so", RTLD_LAZY);
	if(!handle) {
		fprintf(stderr, "dlopen failed: %s\n", dlerror());
		return -1;
	}
	
	void *func = dlsym(handle, "hello");
	if(func) {
		reinterpret_cast<void(*)()>(func)();
	}
	
	dlclose(handle);
}
