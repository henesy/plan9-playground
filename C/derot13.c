#include <u.h>
#include <libc.h>
#include <bio.h>

/* formatting is defined in style(6) ;; compile/link/run: 6c reverse.c; 6l -o 6.reverse reverse.6; ./6.reverse */

/* reverses a string provided on input unless a blank string is provided */
void main(int argc, char *argv[])
{
	/* standard Biobuf at declaration time, &'s to pass pointers */
	Biobuf in, out;

	/* initialize our i/o, fd 0 is stdin, 1 is stdout, 2 is stderr, as is standard */
	if(Binit(&in, 0, OREAD) == Beof)
	{
		exits("Binit error with stdin");
	}
	if(Binit(&out, 1, OWRITE) == Beof)
	{
		exits("Binit error with stdout");
	}

	int len = -1;
	while(len != 0)
	{
		char *str = Brdstr(&in, '\n', 1);
		len = strlen(str);

		int i;
		for(i = 0; i < len -1; i++)
		{
			str[i] -= 13;
		}
		
		Bprint(&out, "%s\n", str);
		
		/* flush the output buffer */
		Bflush(&out);
	}

	/* exit no error */
	exits(nil);
}
