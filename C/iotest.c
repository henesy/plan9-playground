#include <u.h>
#include <libc.h>
#include <stdio.h>

void main()
{
	char str[30];
	fgets(str, 30, 0);
	print("%s\n", str);
}
