// https://raw.githubusercontent.com/wiki/hjl-tools/x86-psABI/x86-64-psABI-1.0.pdf

#include "foo.h"

__attribute__((noinline))
static int getint_local_noinline() {
	return 13;
}

__attribute__((always_inline))
static inline int getint_local_inline() {
	return 11;
}

int main() {
	int e = getint();
	int f = getint();
	structparm s = getstructparm();
	int g = 17;
	int h = getint();
	long double ld = getlongdouble();
	double m = getdouble();
	double n = getdouble();
	int i = getint_local_inline();
	int j = getint();
	int k = getint_local_noinline();
	__m256 y = getm256();
	__m512 z = getm512();
	
	func(e, f, s, g, h, ld, m, y, z, n, i, j, k);
}
