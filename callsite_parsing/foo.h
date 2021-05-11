#include <immintrin.h>
#include <xmmintrin.h>

typedef struct {
  int a, b;
  double d;
} structparm;

extern void func(int e, int f, structparm s, int g, int h, long double ld,
                 double m, __m256 y, __m512 z, double n, int i, int j, int k);

extern int getint();
extern double getdouble();
extern long double getlongdouble();
extern structparm getstructparm();
extern __m256 getm256();
extern __m512 getm512();
