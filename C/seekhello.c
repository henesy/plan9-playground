#include <u.h>
#include <libc.h>

void
main(int, char*[])
{
	int		fd;
	
	fd = open("afile", OWRITE);
	seek(fd, 32, 0);
	close(fd);
	exits(nil);
	// chmod +a /path/to/file #adds the append-only byte for p9 fs
}
