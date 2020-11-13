/* Andres Lacayo
 * Fundamentals of Computing 
 * crossfunc.c
 * Function definitions for the crossword program
 */

#include "crossfunc.h"
#include<string.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include <time.h> //Helps with the randomizing

//Display the puzzle version of the crossword
void displayPuzzle(char board[][SIZE]){
    int i,n;
    printf("\n");

    printf("Puzzle:\n\n   ");

    for (i = 0; i < SIZE ; i++){
        printf("%c",i+97);
    }
    printf("\n  ");
    for(i = 0; i < SIZE + 2; i++){ //Display Top Row
        printf("-");
    } 
    printf("\n");

    //Display everything in the middle, AKA the board array
    for (i = 0; i < SIZE ; i++){ 
        printf("%2d|",i);
        for (n = 0; n < SIZE; n++){
            if(board[i][n] == ' '){
                printf("#");
            } else {
                printf(" ");
            }
        }
        printf("|\n");
    }
    printf("  ");
    for(i = 0; i < SIZE + 2; i++){ //Display Bottom Row
        printf("-");
    }    
    printf("\n");
}

//Display the solved version of the crossword
void displaySolved(char board[][SIZE]){
    int i,n;
    printf("\n");

    printf("Solution:\n");

    for(i = 0; i < SIZE + 2; i++){ //Display Top Row
        printf("-");
    } 
    printf("\n");

    //Display everything in the middle, AKA the board array
    for (i = 0; i < SIZE ; i++){ 
        printf("|");
        for (n = 0; n < SIZE; n++){
            if(board[i][n] == ' '){
                printf(".");
            } else {
                printf("%c",board[i][n]);
            }
        }
        printf("|\n");
    }

    for(i = 0; i < SIZE + 2; i++){ //Display Bottom Row
        printf("-");
    }    
    printf("\n");

}

void initBoard(char board[][SIZE]){
    int i,n;
    for(i = 0; i < SIZE; i++){
        for(n = 0; n < SIZE ; n++){
            board[i][n] = ' ';
        }
    }
       
}

//Use bubble sort to sort the words from longest to shortest
void sort(word words[SIZE],int count){
    int i, n;
    char temp[SIZE];
    for (i = 0; i < count-1 ; i++){
        for(n = 0; n < count-i-1 ; n++){
            if(strlen(words[n].text) < strlen(words[n+1].text)){
                strcpy(temp,words[n+1].text);
                strcpy(words[n+1].text,words[n].text);
                strcpy(words[n].text,temp);
            }
        }
            
    }
}

void makeCaps(word words[SIZE], int count){
    int i, n;
    for(i = 0; i < count; i++){
        for(n = 0; n < (strlen(words[i].text));n++){
            words[i].text[n] = (char)toupper(words[i].text[n]);
        }
    }
}


void placeWord(word word, char board[][SIZE]){
    int i;
    if(word.orientation == 'h'){
        for(i = 0; i < strlen(word.text); i++ ){
            board[word.row][i+word.col] = word.text[i];
        }
    } else {
        for(i = 0; i < strlen(word.text); i++ ){
            board[i+word.row][word.col] = word.text[i];
        }
    }
}

//Very big function, yes, I was scared of doing nested functions because of last lab

int findIntersection(word words[], char board[][SIZE], int currentWord){
    int i,n,j,isFound = 0, tempCol, tempRow, isInvalid , row, col;
    //i is the word it is comparing with
    //n is the index of the character in the current word
    //j is the index of the character of word i
    for (i = 0; i < currentWord; i++){
        if(isFound == 1) break;
        for (n = 0; n < strlen(words[currentWord].text) ;n++){
            if(isFound == 1) break;
            for (j = 0; j < strlen(words[i].text); j++){
                if(isFound == 1) break;
                // printf("%c %c\n",words[currentWord].text[n],words[i].text[j]);
                if(words[currentWord].text[n] == words[i].text[j]){
                    // printf("found?");
                    if(words[i].orientation == 'h'){
                        tempCol = words[i].col + j;
                        tempRow = words[i].row - n;
                    } else {
                        tempCol = words[i].col - n;
                        tempRow = words[i].row + j;
                    }

                    //Check that all the words are at least one space apart from one another
                    isInvalid = 0;
                    if(words[i].orientation == 'h'){
                        if(isalpha(board[tempRow - 1][tempCol]) || isalpha(board[tempRow + strlen(words[currentWord].text)][tempCol])){
                            // printf("1111");
                            isInvalid = 1;
                        }
                        for(row = 0; row < strlen(words[currentWord].text); row++){
                            if((row + tempRow) == words[i].row) continue;
                            if(board[row + tempRow][tempCol] != ' ' || board[row + tempRow][tempCol-1] != ' ' || board[row + tempRow][tempCol + 1] != ' '){
                                isInvalid = 1;
                                // printf("2222");
                            }
                        }
                        if(isInvalid == 1) continue;

                    } else {
                        if(isalpha(board[tempRow][tempCol - 1]) || isalpha(board[tempRow][tempCol + strlen(words[currentWord].text)])){
                            isInvalid = 1;
                            // printf("3333");
                        }
                        for(col = 0; col < strlen(words[currentWord].text); col++){
                            if((col + tempCol) == words[i].col) continue;
                            if(board[tempRow][col + tempCol] != ' ' || board[tempRow + 1][col + tempCol] != ' ' || board[tempRow - 1][col + tempCol] != ' '){
                                isInvalid = 1;
                                // printf("4444");
                            }
                        }
                        
                    }

                    //Check out of bounds.

                    if(words[i].orientation == 'h'){
                        if(tempRow + strlen(words[currentWord].text) > SIZE  || tempRow < 0){
                            // printf("5555");
                            isInvalid = 1;
                        }
                    } else {
                        if(tempCol + strlen(words[currentWord].text) > SIZE  || tempCol < 0){
                            // printf("6666");
                            isInvalid = 1;
                        }
                    }
                    if(isInvalid == 1) continue;
                    
                    //The loop only reaches this point if all of the conditions are met

                    // printf("FoundGood");
                    isFound = 1;
                    if(words[i].orientation == 'h'){
                        words[currentWord].orientation = 'v';
                    } else {
                        words[currentWord].orientation = 'h';
                    }
                    words[currentWord].row = tempRow;
                    words[currentWord].col = tempCol;
                    
                }
            }    
        }
    }

    return isFound;


}

void outputFile(char filename[], char board[][SIZE], word words[], int count){
    FILE *fout = fopen(filename,"w");
    int i,n;

    //Display the Puzzle

    fputs("\n",fout);

    fputs("Puzzle:\n",fout);

    for(i = 0; i < SIZE + 2; i++){ //Display Top Row
        fputc('-',fout);
    } 
    fputs("\n",fout);

    //Display everything in the middle, AKA the board array
    for (i = 0; i < SIZE ; i++){ 
        fputc('|',fout);
        for (n = 0; n < SIZE; n++){
            if(board[i][n] == ' '){
                fputc('#',fout);
            } else {
                fputc(' ',fout);
            }
        }
        fputs("|\n",fout);
    }

    for(i = 0; i < SIZE + 2; i++){ //Display Bottom Row
        fputs("-",fout);
    }    
    fputs("\n",fout);


    //Display the Solution

    fputs("\n",fout);

    fputs("Solution:\n",fout);

    for(i = 0; i < SIZE + 2; i++){ //Display Top Row
        fputc('-',fout);
    } 
    fputs("\n",fout);

    //Display everything in the middle, AKA the board array
    for (i = 0; i < SIZE ; i++){ 
        fputc('|',fout);
        for (n = 0; n < SIZE; n++){
            if(board[i][n] == ' '){
                fputc('.',fout);
            } else {
                fputc(board[i][n],fout);
            }
        }
        fputs("|\n",fout);
    }

    for(i = 0; i < SIZE + 2; i++){ //Display Bottom Row
        fputs("-",fout);
    }    
    fputs("\n",fout);

    fprintf(fout,"\n");
    // Display Clues

    int letterCount,index,usedIndex[SIZE] = {0};
    char direction[10];
    srand(time(0));
    fprintf(fout,"Clues:\n\n");
    fprintf(fout,"Location | Direction | Anagram\n");
    fprintf(fout,"----------------------------------\n");

    for (i = 0; i < count ; i++){
        if(words[i].orientation == 'h'){
            strcpy(direction,"Across");
        } else {
            strcpy(direction,"Down");
        }
        fprintf(fout,"   %2d,%2d |    %6s | ",words[i].row,words[i].col,direction);
        letterCount = 0;
        while(letterCount < strlen(words[i].text)){
            index = rand() % strlen(words[i].text);
            if(usedIndex[index] == 0){
                usedIndex[index] = 1;
                fprintf(fout,"%c",words[i].text[index]);
                letterCount++;
            }


        }
        for(n = 0; n < SIZE ; n++){
            usedIndex[n] = 0;
        }
        fprintf(fout,"\n");
    }
}



void displayClues(word words[],int count){
    int i,n,letterCount,index,usedIndex[SIZE] = {0};
    char direction[10];
    srand(time(0));
    printf("Clues:\n\n");
    printf("Location | Direction | Anagram\n");
    printf("----------------------------------\n");

    for (i = 0; i < count ; i++){
        if(words[i].orientation == 'h'){
            strcpy(direction,"Across");
        } else {
            strcpy(direction,"Down");
        }
        printf("   %2d,%c |    %6s | ",words[i].row,words[i].col+97,direction);
        letterCount = 0;
        while(letterCount < strlen(words[i].text)){
            index = rand() % strlen(words[i].text);
            if(usedIndex[index] == 0){
                usedIndex[index] = 1;
                printf("%c",words[i].text[index]);
                letterCount++;
            }


        }
        for(n = 0; n < SIZE ; n++){
            usedIndex[n] = 0;
        }
        printf("\n");
    }
}


