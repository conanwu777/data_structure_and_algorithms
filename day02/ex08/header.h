#ifndef HEADER_H
# define HEADER_H

/*--------------------------------
  !! required structure
  --------------------------------*/
#define SCOREFILE "grannyScores.txt"
#define SORTEDFILE "grannyScoresSorted.txt"

struct s_block {
	int *scores;
	int n;
};

/*--------------------------------
  :) function you must implement
  --------------------------------*/
void externalSort(char *scoreFile, char *sortedFile, int ram);

/*--------------------------------
  ?? test function used in main
  --------------------------------*/
FILE *openFile(char *filename, char *flag);

int readBlock(FILE *f, int *arr, int size);

void writeFile(char *filename, int *arr, int n);

int fileIsSorted(char *filename);

struct s_block *fileGetBlock(char *filename, int start, int end);
int filePutBlock(char *filename, struct s_block *block);
int fileGetTotalScores(char *filename);

/*--------------------------------
  &  your own other function
  --------------------------------*/


#endif
