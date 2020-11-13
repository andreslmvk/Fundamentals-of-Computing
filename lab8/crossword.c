/* Andres Lacayo
 * Fundamentals of Computing 
 * crossword.c
 * Main driver of the corssword program
 */

#include<stdio.h>
#include "crossfunc.h"
#include<string.h>
#include<ctype.h>
#include<math.h>

//Size = 15
//Max Words = 20
//Row and column coordinates start from 0
int main(int argc, char *argv[]) {
    int i,n,count = 0,isValid = 0,currentWord = 1,isFound; 
    char board[SIZE][SIZE];
    char input[SIZE];
    word words[MAXWORDS];
    FILE *fp;
 
    initBoard(board);

    //Input words and check if words are valid
    if(argc ==1){
        while(count <= 20){
            printf("Input Word (Enter '.' when you are finished): ");
            scanf("%s",input);

            if(input[0] == '.' && strlen(input) == 1){
                break;
            }

            if(strlen(input) < 2){
                printf("Word is too short\n");
                continue;
            } else if (strlen(input) > 15){
                printf("Word is too long\n");
                continue;
            }
            for(i = 0; i < strlen(input) ; i++){
                if(isalpha(input[i]) == 0){
                    printf("Word contains something that is not a letter\n");
                    isValid++;
                    break;
                }
            }
            if(isValid != 0){
                continue;
            }

            strcpy(words[count].text,input);
            count++;
        }


    //Check that there are 2 or 3 arguments, get the second one and use it as an input file

    } else if(argc < 4){
        fp = fopen(argv[1],"r");
		if(!fp){
			printf("%s not found\n",argv[1]);	
		}
        //Record each word, checks for either a period or eof 
        while(1){ //Maybe check if input is valid
            fscanf(fp,"%s",input);
            if(input[0] == '.' && strlen(input) == 1){
                break;
            }
            if(feof(fp)) break;
            strcpy(words[count].text,input);
            count++;
        }
        fclose(fp);

        //Return an error if there are too many arguments
    } else {
        printf("Too many arguments\n");
        return 1;
    }

    //Make all the words caps and sort them from longest to shortest
    makeCaps(words,count);
    sort(words,count);



    //Place first (longest) word in the middle of the board (record coordinates) (8th row always) DONE
    // Get next word and check if they intersect and Check if words have valid placement (repeat)
    //If not, end 
    //Vertical vs horizontal placement
    //Check if there is a space in between
    //Check that it intersects with only one word

    //Since the first word is a special case, I will just put it here, no need for a function

    //Find coordinates
    words[0].row = 7;
    words[0].col = floor((SIZE - strlen(words[0].text))/2);
    words[0].orientation = 'h'; //Set orientation
    placeWord(words[0],board); //Place word in board


    //Place the rest of the words in the board
    for (i = 1; i < count ; i++){
        isFound = findIntersection(words,board,i);
        if(isFound == 0){
            printf("Not found\n");
            return 1;
        }
        placeWord(words[i],board);
        // displaySolved(board);
    }


    displayPuzzle(board);
    displaySolved(board);
    displayClues(words,count);


    if(argc == 3){
        outputFile(argv[2], board, words, count);
    }

 
    return 0;
}

