#include <u.h>
#include <libc.h>

void
main(int, char*[])
{
	char	buffer[1024];
	int		fd, nr;
	/*
	nr = read(0, buffer, sizeof buffer);
	write(1, buffer, nr);
	*/
	fd = open("/dev/cons", ORDWR);
	nr = read(fd, buffer, sizeof buffer);
	write(fd, buffer, nr);
	close(fd);

	exits(nil);
}
