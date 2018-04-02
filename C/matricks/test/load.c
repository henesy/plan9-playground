#include <u.h>
#include <libc.h>
#include <matrix.h>

// Tests loading and unloading a matrix from a csv
void
main()
{
	int fd1 = open("1.csv", OREAD);
	int fd2 = open("2.csv", OREAD);
	Matrix* m1 = mktrix(fd1);
	Matrix* m2 = mktrix(fd2);
	
	exits(nil);
}
