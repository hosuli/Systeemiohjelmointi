/*
	CT30A3370 Käyttöjärjestelmät ja systeemiohjelmointi
	Siiri Pajunen
*/


#include <stdio.h>
#include <stdlib.h>
#define MAXLENGTH 512

int main(int argc, char * argv[]) {
	
	//exit returning 0 when no files have been specified
	if (argc == 1) {
		//printf("No file(s) specified\n");
		exit(0);
	}

	int i = 1;
	
	//going through all files given
	for (i=1; i < argc; i++) {
		FILE *fp = fopen(argv[i], "r");
		//checking if file can be opened
		if (fp == NULL) {
			printf("wcat: cannot open file\n");
			exit(1);
		}
		
		char buffer[MAXLENGTH];
		//going through all lines in the file currently open and printing them
		while (fgets(buffer, MAXLENGTH, fp) != NULL) {
			printf("%s", buffer);
		}
		fclose(fp);
	}
	return 0;
}
