#include <stdio.h>

void main()
{
	char str[30];
	fgets(str, 30, stdin);
	printf("%s\n", str);
}
