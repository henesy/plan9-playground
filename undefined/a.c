#include <u.h>
#include <libc.h>

void
main()
{
	int x = 0;
	int res = (x = 1) + (x = 2);
	print("%d\n", res);
	exits(nil);
}
