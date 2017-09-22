#include <u.h>
#include <libc.h>

int*
foo(int x)
{
	int z = x;
	int *y = &z;
	return y;
}

void
main()
{
	int* x = foo(0);
	foo(255);
	int res = *x;
	print("%d\n", res);
	exits(nil);
}
