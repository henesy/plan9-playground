#include <u.h>
#include <libc.h>

void
main(int, char*argv[])
{
	/* Wrong! */
	print("hi ");
	print(argv[1]);
	exits(nil);
	/* upon errors `src` can be used on the pc= value */
}
