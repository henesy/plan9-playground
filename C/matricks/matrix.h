#ifndef MTRX_H
#define MTRX_H
#pragma lib "libmatricks.a"

/* vars -- by default, a max integer width of 256 is set (mutable) */
#define MAXWIDTH 256

/* structures */
typedef struct Matrix Matrix;

/* h → height, w → width, d → data */
struct Matrix {
	int fd;
	int h;
	int w;
	int** d;
};

/* functions */
Matrix* mktrix(int);

#endif
