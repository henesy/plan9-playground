#include <u.h>
#include <libc.h>
#include <bio.h>
#define maxbuf 12500000
#define width 100000000000000

void
main()
{
	Biobufhdr bp;
	int i;
	uchar buf[maxbuf];
	Binits(&bp, 1, OWRITE, buf, sizeof(buf));

	for(i = 0; i < width; i++)
		Bputc(&bp, '0');

	Bflush(&bp);
	Bterm(&bp);
	exits(nil);
}
