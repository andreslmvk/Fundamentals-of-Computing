/* Andres Lacayo
 * Fundamentals of Computing 
 * lifefunc.h
 * File that contains the prototypes of the functions for the game of life.
 */

#include<stdio.h>
#define SIZE 40
void displayBoard(char[SIZE][SIZE]); //Displays current board
int checkIfAlive(char[SIZE][SIZE],int,int); //Check if a cell is alive
void step(char[SIZE][SIZE]); //Generates the next step of the simulation
void initBoard(char[][SIZE]); //Fill the board with zeros
void displayMenu(void); //Display the menu for the user