#include "foo.h"

void func(int e, int f, structparm s, int g, int h, long double ld,
                 double m, __m256 y, __m512 z, double n, int i, int j, int k)
{
	(void)e;
	(void)f;
	(void)s;
	(void)g;
	(void)h;
	(void)ld;
	(void)m;
	(void)y;
	(void)z;
	(void)n;
	(void)i;
	(void)j;
	(void)k;
}

int getint() {return 7;}
double getdouble(){ return 7.0; }
long double getlongdouble(){ return 7.0; }
structparm getstructparm(){structparm s = {7,0,7.0}; return s;}

__m256 getm256(){ return _mm256_set1_ps(7.0f); }
__m512 getm512(){ return _mm512_set1_ps(7.0f); }
