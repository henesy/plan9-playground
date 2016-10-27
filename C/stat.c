#include <u.h>
#include <libc.h>

void
usage(void)
{
	fprint(2, "usage: %s [-f filepath]\n", argv0);
	exits("usage");
}

void
main(int argc, char* argv[])
{
	char fpath[200];
	int pos;
	ARGBEGIN{
	case 'f':
		//pos = ARGC();
		strcat(fpath, EARGF(usage()));
		//fprint(2, "%s\n", fpath);
		if(strlen(fpath) < 1)
			usage();
		break;
	}ARGEND;
	
	if(!(strlen(fpath) > 0)) {
		strcat(fpath, "/NOTICE");
	}

	Dir*	d;

	d = dirstat(fpath);
	if (d == nil)
		sysfatal("dirstat: %r");
	print("file name: %s\n", d->name);
	print("file mode: O%o\n", d->mode);
	print("file size: %d bytes\n", d->length);
	free(d);
	exits(nil);
}
