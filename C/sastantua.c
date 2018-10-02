#include <u.h>
#include <libc.h>

int		ft_math(int row, int desiredreturn, int i);
void	ft_print_row(int max_chars, int chars, int door);
void	sastantua(int size);

void
usage(void)
{
	fprint(2, "usage: sastantua [-n size]\n");
	exits("usage");
}

/* Build a tiered pyramid of a specified size ≥ 1 (defaulting to 1) */
void
main(int argc, char *argv[])
{
	int	i = 0;
	int	size = 1;

	ARGBEGIN {
	case 'n':
		size = atoi(EARGF(usage()));
		break;
	default:
		usage();
	} ARGEND
	
	if(size < 1)
		usage();

	sastantua(size);

	exits(nil);
}

/* Takes in size and builds pyramid */
void
sastantua(int size)
{
	int	i;
	int	max_row;
	int	max_chars;

	max_row = ft_math(0, 1, size);
	max_chars = ft_math(max_row, 4, 0);
	if(size > 0) {
		if(size % 2 == 0)
			size = size -1;

		for(i = 1; max_row > 0; max_row--, i++)
			ft_print_row(max_chars, ft_math(i, 4, 0), size);
	}
}

/*
 * ft_print_row takes in the number of characters at the bottom of our
 * pyramid (max_chars), the number of characters in our current row (chars),
 * and the size of our door (door), and assembles our pyramid level by level
 * with the information. 
 */

void
ft_print_row(int max_chars, int chars, int door)
{
	int	i;

	for(i = 0; i < max_chars; i++){
		if(i < (max_chars / 2) - (chars / 2) || i > (max_chars / 2) + (chars / 2)){
			write(1, " ", 1);
		
		}else if (i == (max_chars / 2) - (chars / 2) || i == (max_chars / 2) + (chars / 2)) {
			if(i == (max_chars / 2) - (chars / 2))
				write(1, "/", 1);
			else
				write(1, "\\", 1);
		
		}else if (max_chars - chars <= door * 2 - 1 && (i >= (max_chars / 2) - (door / 2) && i <= (max_chars / 2) + (door / 2))){ 
			
			if(door > 3 && i == (max_chars / 2) + (door / 2) - 1 && max_chars - chars == door - 1)
				write(1, "$", 1);
			else
				write(1, "|", 1);
		
		}else{
			write(1, "*", 1);
		}
	}

	write(1, "\n", 1);
}

/*
 * ft_math does all of the heavy lifting when it comes to crunching the
 * numbers for our pyramid.
 * 
 * Since there are different calculations needed for building our pyramid
 * correctly, we need to tell our math function what our desired return is.
 * 
 * The keys for desired return are as follows: 1 = The maximum number of rows 
 * for size i 2 = Tier that current row is in 3 = Character progression for
 * tier changes 4 = Number of characters in row i 
 */

int
ft_math(int row, int desiredreturn, int i)
{
	if(desiredreturn == 1){
		if(i == 1)
			return 3;
		else
			return (i + 2) + ft_math(0, 1, i - 1);
	}

	if(desiredreturn == 2){
		if(row > 3)
			if(row > ft_math(0, 1, i))
				return ft_math(row, 2, i + 1);
			else 
				return i;

		return 1;
	}

	if(desiredreturn == 3){
		if (i % 2 == 0)
			return i + 4;
		else
			return i + 3;
	}

	if(row > 1){
		if(ft_math(row, 2, 1) == ft_math(row - 1, 2, 1))
			return 2 + ft_math(row - 1, 4, ft_math(0, 3, ft_math(row - 1, 2, 1)));
		else
			return ft_math(0, 3, ft_math(row, 2, 1)) + ft_math(row - 1, 4, ft_math(0, 3, ft_math(row - 1, 2, 1)));
	}

	return 3;
}
