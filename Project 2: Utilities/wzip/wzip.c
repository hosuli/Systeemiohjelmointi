/*
	CT30A3370 Käyttöjärjestelmät ja systeemiohjelmointi
	Siiri Pajunen
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

	int character = -1;
	int counter = -1;
    	//int buffer;
	
	//only argument is the program name, no files given
	if (argc == 1) {
		printf("wzip: file1 [file2 ...]\n");
		exit(1);
	}
	//file or files are given as arguments
	else if (argc >= 2) {
		int buffer;
		for (int i=1; i < argc ; i++) {
			FILE *fp = fopen(argv[i], "r");
			//checking if file can be opened
			if (fp == NULL) {
				//printf("wzip: cannot open file\n");
				exit(1);
			}
			//while loop for going through all characters in file
			while (1) {
				buffer = fgetc(fp);
				//break out of loop when end of current file reached
                		if (buffer == EOF){
                    			break;
                		}
                		//increase counter
		        	if(buffer == character) {
					counter++;
				} //write counter and character
				else if (counter > 0){
					fwrite(&counter, 4, 1, stdout);
					fwrite(&character, 1, 1, stdout);
					character = buffer;
					counter = 1;
				} else {
					character = buffer;
					counter = 1;
				}			 
			}			
			fclose(fp);
		}
	}	
        if (counter > 0) {
		fwrite(&counter, 4, 1, stdout);
		fwrite(&character, 1, 1, stdout);
			}
	return 0;
}
