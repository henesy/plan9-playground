#include <u.h>
#include <libc.h>

void
main(int, char*[])
{
	char*	home;
	
	home = getenv("home");
	/* there is also putenv() which is invoked:
	putenv(name, val); //places val value in env name name */
	if (home == nil)
		sysfatal("we are homeless");
	print("home is %s\n", home);
	exits(nil);
}
