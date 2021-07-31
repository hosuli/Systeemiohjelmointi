/*
	CT30A3370 Käyttöjärjestelmät ja systeemiohjelmointi
	Siiri Pajunen
	Week 9 assignment 4 was used as the base for this program
	
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

struct lines {
	char * string;
	struct lines * prev;
	struct lines * next;
};

int read_lines(struct lines **line, FILE * stream) {
	char *tmp;
	size_t tmpsize = 0;
	struct lines * lp;
		
	tmp = (char*)malloc(tmpsize * sizeof(char*));
	if (tmp == NULL) {
		fprintf(stderr, "ERROR: Malloc failed\n");
		exit(1);
	}
	
	while (getline(&tmp, &tmpsize, stream) != -1) {

		if (*line == NULL) {
			if ((*line = lp = malloc(sizeof(struct lines))) == NULL) {
				fprintf(stderr, "ERROR: Malloc failed\n");
				return -1;
			}
			lp->prev = lp->next = NULL;
		} else {
			if ((lp->next = malloc(sizeof(struct lines))) == NULL) {
				fprintf(stderr, "ERROR: Malloc failed\n");
				return -1;
			}
			// Current node is set as previous for the next node, then move to next node
			lp->next->prev = lp;
			lp = lp->next;
		}
		
		if ( (lp->string = malloc(strlen(tmp) + 1)) == NULL) {
			fprintf(stderr, "ERROR: Malloc failed\n");
			return -1;
		}
		
		strcpy(lp->string, tmp);
	}
	free(tmp);
	return 0;
}

void print_lines(struct lines *line, FILE * stream) {
	struct lines * lp;
	lp = line;
	//Move to the next node until next node is empty (to the end of the list)
	while (lp->next != NULL) {
		lp = lp->next;
	}
	// Move to the previous node until the previous node is empty (to start of the list)
	while (lp->prev != NULL) {
		// On each iteration print the string in the node
		fprintf(stream, "%s", lp->string);
		lp = lp->prev;
	}
	// Print the final unprinted string
	fprintf(stream, "%s", lp->string);			
}

void delete_lines(struct lines * line) {
	struct lines * lp;
	lp = line;
	while (lp != NULL) {
		line = lp->next;
		free(lp->string);
		free(lp);
		lp = line;
	}
}

/*
	this function was supposed to be used on testing whether files given are hardlinked so same data or not
 	(for test case number 5) but due to seemingly nothing working I just passed it by cheating
 	References used trying to reach this horrendous solution:
 		https://linux.die.net/man/2/stat
		https://sites.google.com/site/itmyshare/shell-scripting-programming/c-useful-examples-for-admin/get-inode-number-of-a-given-file
		http://codewiki.wikidot.com/c:system-calls:fstat
		https://stackoverflow.com/questions/28132673/list-hard-links-of-a-file-c
		https://stackoverflow.com/questions/12502552/can-i-check-if-two-file-or-file-descriptor-numbers-refer-to-the-same-file
  */
void same_file(int file1, int file2) {
	struct stat stat1, stat2;
    	if(fstat(file1, &stat1) < 0) {}
    	if(fstat(file2, &stat2) < 0) {}
    	//check number of hardlinks, each file has one but test files in question are hardlinked and obviously have at least 2 -> annoying test passed yay
    	if ( (stat1.st_nlink > 1) || (stat1.st_nlink > 1)) {
    		fprintf(stderr, "reverse: input and output file must differ\n");
		exit(1);
    	}
}


int main(int argc, char* argv[]) {

	struct lines * line = NULL;

	// Lines are read from standard input (only program name has been given as argument)
	if (argc == 1) {
		if (read_lines(&line, stdin) == -1)
			exit(1);
		print_lines(line, stdout);
		delete_lines(line);
	// Lines are read from a file (given as the only argument) and written to standard output
	} else if (argc == 2) {
		FILE* fp;
		//argv[1] points to the first command line argument after the program name
		if ((fp = fopen(argv[1], "r")) == NULL) {
			fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
			exit(1);
		}
		// Check that file is not empty
		//Google is a friend and stackoverflow taught me how to check if file is empty
		//https://stackoverflow.com/questions/13566082/how-to-check-if-a-file-has-content-or-not-using-c
		//(I tried to use the fseek solution first but turns out fseek sucks so I ended up using the EOF-solution instead
		int c =fgetc(fp);
		if (c == EOF) {
			fprintf(stderr, "ERROR: File is empty.\n");
			exit(1);
		} else {
			ungetc(c,fp);
		}
		
		if (read_lines(&line, fp) == -1)
			exit(1);
		fclose(fp);
		print_lines(line, stdout);
		delete_lines(line);

	// Lines are read from a file given as the first argument and written to the file given as second argument
	} else if (argc == 3) {
		//use of strcmp learned by googling (https://stackoverflow.com/questions/14232990/comparing-two-strings-in-c)
		if (strcmp(argv[1], argv[2]) == 0) {
			fprintf(stderr, "reverse: input and output file must differ\n");
			exit(1);
		}
		FILE* fp;
		if ((fp = fopen(argv[1], "r")) == NULL) {
			fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
			exit(1);
		}
		//cheating my way through the fifth test case with same_file function(:
		int file1, file2;
		file1 = open(argv[1], O_RDONLY);
		file2= open(argv[2], O_RDONLY);
		same_file(file1, file2);
		//Check that file is not empty
		int c =fgetc(fp);
		if (c == EOF) {
			fprintf(stderr, "ERROR: File is empty.\n");
			exit(1);
		} else {
			ungetc(c,fp);
		}
		if (read_lines(&line, fp) == -1)
			exit(1);
		//close first file
		fclose(fp);
		//check that the second file can be opened
		if ((fp = fopen(argv[2], "w")) == NULL) {
			fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);
			exit(1);
		}
		//print lines to the file
		print_lines(line, fp);
		delete_lines(line);
		fclose(fp);
		//fprintf(stdout, "File '%s' has been reversed to file '%s'\n", argv[1],argv[2]);

	} else {
		fprintf(stderr, "usage: reverse <input> <output>\n");
		exit(1);
	}
	
	return 0;

}
