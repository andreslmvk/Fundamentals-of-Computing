/* Andres Lacayo
 * Fundamentals of Computing 
 * lifefunc.c
 * File that stores all of the functions of the game of life.
 */

#include "lifefunc.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Function to display the board in the current state (The board goes from 1 to 40, instead of using the index of 0 to 39)
void displayBoard(char board[SIZE][SIZE]){
    int i,n;
    printf("\n");
    system("clear");

    for(i = 0; i < SIZE + 2; i++){ //Display Top Row
        printf("-");
    } 
    printf("\n");

    //Display everything in the middle, AKA the board array
    for (i = 0; i < SIZE ; i++){ 
        printf("|");
        for (n = 0; n < SIZE; n++){
            printf("%c",board[i][n]);
            
        }
        printf("|\n");
    }

    for(i = 0; i < SIZE + 2; i++){ //Display Bottom Row
        printf("-");
    }    
    printf("\n");
}

//Function that checks if the cell in the given index is alive or not, 
//the input should be in index of the array rather than coordinate in the board

int checkIfAlive(char board[SIZE][SIZE], int row, int col){
    int livingNeighbors = 0, i ,n;

    //Count the living neighbors using a nested for loop
    for(i = (row-1); i <= row+1 ; i++){
        for(n = (col-1); n <= col+1; n++){
            if(i < 0 || i >= SIZE || n < 0 || n >= SIZE || (i == row && n == col)){
                continue;
            }
            if(board[i][n] == 'X'){
                livingNeighbors++;
            }


        }
    }

//A dead cell with exactly 3 neighbors becomes live; and only a live cell with 2 or 3 neighbors survives, all others die.
    //Check if the return value is that of a living cell or that of a dead cell
    if(board[row][col] == 'X' && (livingNeighbors == 3 || livingNeighbors == 2)){
        return 1;
    } else if(board[row][col] == ' ' && livingNeighbors == 3) {
        return 1;
    } else {
        return 0;
    }


}




//Generates the new step in the simulation using the rules:
//A dead cell with exactly 3 neighbors becomes live; and only a live cell with 2 or 3 neighbors survives, all others die.
void step(char board[][SIZE]){
    int tempBoard[SIZE][SIZE];
    int row, col, isAlive;
//Loop through the board to check the life of each cell.
    for(row = 0; row < SIZE ; row++){
        for(col = 0; col < SIZE ; col++){
            isAlive = checkIfAlive(board, row, col);
            if(isAlive == 0){
                tempBoard[row][col] = ' ';
            } else {
                tempBoard[row][col] = 'X';
            }
        }
            
    }
    //Now pass the data from the temp board to the real board using a nested for loop

    for(row = 0 ; row < SIZE ; row++){
        for(col = 0; col < SIZE ; col++){
            board[row][col] = tempBoard[row][col];
        }
    }


}

//Function that initializes the board with empty spaces, uses a nested for loop.
void initBoard(char board[][SIZE]){
    int i,n;
    for(i = 0; i < SIZE; i++){
        for(n = 0; n < SIZE ; n++){
            board[i][n] = ' ';
        }
    }
   
}

void displayMenu(void){
	printf("\nOptions:\n");
	printf("-Add a cell: \"a # #\" (# is a coordinate between 1 and 40)\n");
	printf("-Remove a cell: \"r # #\" (# is a coordinate between 1 and 40)\n");
	printf("-Next Generation: \"n\"\n");
	printf("-Quit: \"q\"\n");
	printf("-Play Simulation: \"p\"\n\n");
	printf("Your Input: ");
}	






