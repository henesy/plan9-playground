#include <u.h>
#include <libc.h>

int
asgn(int* p, int v)
{
	return (*p = v);
}

void
main()
{
	int x = 0;
	int res = asgn(&x,1) + asgn(&x,2);
	print("%d\n", res);
	exits(nil);
}
