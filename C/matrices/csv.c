#include <stdio.h>
#include <stdlib.h>

void
main()
{
	int i, j, w0 = 0, w1 = 0, h0 = 0, h1 = 0, firstline = 1;
	char fname0[] = "0.csv";
	char fname1[] = "1.csv";
	int** m0;
	int** m1;
	char c;
	FILE* f0 = fopen(fname0, "r");
	FILE* f1 = fopen(fname1, "r");

	if(f0 == NULL){
		fprintf(stderr, "Error: Unable to open file %s.\n", fname0);
		exit(1);
	}
	if(f1 == NULL){
		fprintf(stderr, "Error: Unable to open file %s.\n", fname1);
		exit(2);
	}
	
	// Scan f0 for dimensions
	while((c = fgetc(f0)) != EOF){
		if(c == '\n'){
			h0++;
			if(firstline)
				w0++;
			
			firstline = 0;
		}
		
		if(c == ',' && firstline)
			w0++;
	}
	
	// Scan f1 for dimensions
	firstline = 1;
	while((c = fgetc(f1)) != EOF){
		if(c == '\n'){
			h1++;
			if(firstline)
				w1++;
			
			firstline = 0;
		}
		
		if(c == ',' && firstline)
			w1++;
	}
	
	printf("\nMatrix 0\nHeight: %d\nWidth: %d\n\n", h0, w0);
	printf("\nMatrix 1\nHeight: %d\nWidth: %d\n\n", h1, w1);
	m0 = calloc(h0, sizeof(int*));
	m1 = calloc(h1, sizeof(int*));
	
	for(i = 0; i < h0; i++){
		m0[i] = calloc(w0, sizeof(int));
	}
	
	for(i = 0; i < h1; i++){
		m1[i] = calloc(w1, sizeof(int));
	}
	
	fseek(f0, 0, SEEK_SET);
	fseek(f1, 0, SEEK_SET);
	
	// Load matrices ;; arbitrary limit of 256 char-wide numbers
	int k = 0;
	char num[256];
	i = 0, j = 0;
	while((c = fgetc(f0)) != EOF && i < h0 && k < 256 && j < w0){
		if(c == ',' || c == '\n'){
			num[k] = '\0';
			m0[i][j] = atoi(num);
			//printf("%d\n", m0[i][j]);
			if(c == ',')
				j++;
			if(c == '\n'){
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
	
	i = 0, j = 0, k = 0;
	while((c = fgetc(f1)) != EOF && i < h1 && k < 256 && j < w1){
		if(c == ',' || c == '\n'){
			num[k] = '\0';
			m1[i][j] = atoi(num);
			//printf("%d\n", m1[i][j]);
			if(c == ',')
				j++;
			if(c == '\n'){
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
	
	// Do maths
	
	// Free and close
	fclose(f0);
	fclose(f1);
	
	for(i = 0; i < h0; i++){
		free(m0[i]);
	}
	for(i = 0; i < h1; i++){
		free(m1[i]);
	}
	free(m0);
	free(m1);
}
