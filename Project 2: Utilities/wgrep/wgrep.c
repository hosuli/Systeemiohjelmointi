/*
	CT30A3370 Käyttöjärjestelmät ja systeemiohjelmointi
	Siiri Pajunen
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int search_term(char termsearched[], FILE* stream){
	char *tmp;
	size_t tmpsize = 0;
	while(getline(&tmp, &tmpsize, stream) != -1) {
		//strstr function is used to "find the needle in the haystack"
		//Found from https://stackoverflow.com/questions/12784766/check-substring-exists-in-a-string-in-c/12784812
		if(strstr(tmp, termsearched) != NULL) {
			printf("%s", tmp);
		}
	}
	free(tmp);
	return 0;
}

int main(int argc, char *argv[]) {

	//int i;
	//When no arguments are given, print out the form in which they are expected
	if (argc == 1){
		printf("wgrep: searchterm [file ...]\n");
		exit(1);
	}
	// searching given string from files given as arguments 
	else if (argc > 2) {
		//go through all files, count starts from 2 because argv[1] is the search-term, not a file
		for (int i=2; i < argc ; i++) {
			FILE *fp = fopen(argv[i], "r");
			//checking if file can be opened
			if (fp == NULL) {
				printf("wgrep: cannot open file\n");
				exit(1);
			}
			//search_term function eats the searchable term argv[1] and the location to search (here it is the file name)
			search_term(argv[1], fp);
			fclose(fp);
		}
		
	}
	//when only the searchable string is given, search from standard input using the oh so fancy search_term function
	else if (argc == 2) {
		search_term(argv[1], stdin);
		
	}
	
	return 0;
}
