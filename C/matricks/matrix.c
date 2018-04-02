#include "matrix.h"
#include <u.h>
#include <libc.h>
#include <bio.h>

/* Open fd and read a csv file into a matrix (checking format) */
Matrix*
mktrix(int fd)
{
	int c, firstline = 1, i, j, k;
	char num[MAXWIDTH];
	Matrix* m = calloc(1, sizeof(Matrix));
	Biobuf* bp = Bfdopen(fd, OREAD);
	m->fd = fd;
	
	/* Note: This could be smarter by caching offset and being relative, then resetting to the cached offset */

	// Grok width & height
	while((c = Bgetc(bp)) > 0){
		if(c == '\n'){
			m->h++;
			if(firstline)
				m->w++;
			
			firstline = 0;
		}
		
		if(c == ',' && firstline)
			m->w++;
	}
	
	Bseek(bp, 0, 0);
	
	m->d = calloc(m->h, sizeof(int*));
	for(i = 0; i < m->h; i++)
		m->d[i] = calloc(m->w, sizeof(int));

	// Load matrix
	i = j = k = 0;
	while((c = Bgetc(bp)) > 0 && i < m->h && k < MAXWIDTH && j < m->w){
		if(c == ',' || c == '\n'){
			num[k] = '\0';
			m->d[i][j] = atoi(num);
			//print("%d\n", m->d[i][j]);
			if(c == ',')
				j++;
			else if(c == '\n'){
				i++;
				j = 0;
			}
			i = 0;
			k = 0;
		}else{
			num[k] = c;
			k++;
		}
	}
	
	Bseek(bp, 0, 0);
	Bflush(bp);
	
	return m;
}
