#include <u.h>
#include <libc.h>
#include <bio.h>
/* obtained via `wc -l /lib/unicode` */
#define UNICODEN 6588

typedef struct tile tile;
typedef struct tile {
	uint score;
	uint value;
};

/*
A small scrabble-style text scoring game.
Recommended usage: `… | awk '{print tolower($0)}' | scrabble`
*/
void
main()
{
	tile runes[UNICODEN];
	int i;
	Biobuf* in = Bfdopen(0, OREAD);
	long r;
	uint score = 0;
	uint maxscore = 0;
	
	/* initialize known scores, easily extended */
	for(i = 0; i < UNICODEN; i++){
		runes[i].score = 0;
		runes[i].value = 0;
	}
	runes['a'].value = 1;
	runes['b'].value = 3;
	runes['c'].value = 3;
	runes['d'].value = 2;
	runes['e'].value = 1;
	runes['f'].value = 4;
	runes['g'].value = 2;
	runes['h'].value = 4;
	runes['i'].value = 1;
	runes['j'].value = 8;
	runes['k'].value = 5;
	runes['l'].value = 1;
	runes['m'].value = 3;
	runes['n'].value = 1;
	runes['o'].value = 1;
	runes['p'].value = 3;
	runes['q'].value = 10;
	runes['r'].value = 1;
	runes['s'].value = 1;
	runes['t'].value = 1;
	runes['u'].value = 1;
	runes['v'].value = 4;
	runes['w'].value = 4;
	runes['x'].value = 8;
	runes['y'].value = 4;
	runes['z'].value = 10;
	
	/* game routine */
	while((r = Bgetrune(in)) > 0){
		runes[r].score++;
	}

	for(i = 0; i < UNICODEN; i++){
		score += runes[i].value * runes[i].score;
		if(runes[i].value > 0 && runes[i].score > 0)
			maxscore += 10 * runes[i].score;
	}
	
	print("Score: %ud\n%lg%% of max possible score\n", score, ((double)score/maxscore)*100);

	Bflush(in);
	Bterm(in);
}
