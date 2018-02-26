#include <u.h>
#include <libc.h>

void
main(int , char * [])
{
	/*
		werrstr("txt"); //writes "txt" to the error string
		char	error[128]; //size might be specific?
		rerrstr(error, sizeof error); //writes error string to 'error' array
	*/
	if (chdir("magic") < 0) {
		/*print("chdir failed: %r\n");
		exits("failed"); */
		sysfatal("chdir failed: %r");
	}
	/* ... do other things ... */
	exits(nil);
}
