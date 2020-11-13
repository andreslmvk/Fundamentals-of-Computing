/* Andres Lacayo
 * Fundamentals of Computing 
 * crossword.h
 * Function prototypes for the crossword program
 */

#define SIZE 15
#define MAXWORDS 20

typedef struct {
    char text[SIZE+1]; //Account for the null character with the plus 1
    char orientation; // 'h' for horizontal, 'v' for vertical
    int row,col;
} word;

void initBoard(char[][SIZE]);
void displayPuzzle(char[][SIZE]);
void displaySolved(char[][SIZE]);
int compareFunction(const void*, const void*);
void sort(word words[SIZE],int);
void makeCaps(word words[SIZE],int);
void placeWord(word word, char board[][SIZE]);
int findIntersection(word [], char [][SIZE],int);
void outputFile(char [],char [][SIZE], word [], int);
void displayClues(word [], int);
