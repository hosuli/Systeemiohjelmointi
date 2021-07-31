/*
	CT30A3370 Käyttöjärjestelmät ja systeemiohjelmointi
	Siiri Pajunen
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	//only argument is the program name, no files given
	if (argc == 1) {
		printf("wunzip: file1 [file2 ...]\n");
		exit(1);
	} 
	//file or files are given as arguments
	else if (argc >= 2) {
		int counter = -1;
		int character = -1;
		for (int i=1; i < argc ; i++) {
			FILE *fp = fopen(argv[i], "r");
			//checking if file can be opened
			if (fp == NULL) {
				printf("wunzip: cannot open file\n");
				exit(1);
			}
			int loop = 1;
			//go through zipped characters
			while (loop == 1) {
				if (fread(&counter, 4, 1, fp) > 0 && fread(&character, 1, 1, fp) > 0) {
					for (int i=0; i < counter; i++) {
						printf("%c", character);
					}
				} else {
					loop = 0;
				}
			}
			fclose(fp);
		}
	}
	return 0;
}


