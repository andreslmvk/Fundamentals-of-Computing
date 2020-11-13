/* Andres Lacayo
 * Fundamentals of Computing 
 * playlife.c
 * Main driver of the game of life.
 */

#include<stdio.h>
#include "lifefunc.h" //Defines size as 40 as well
#include<unistd.h> //Library for usleep

//Function Prototypes

int main(int argc, char * argv[]) {
    char board[SIZE][SIZE];
    int i,n, isRunning = 0;
    FILE *fp;
    // char command[6];
    int sleepTime = 200000;


    initBoard(board); // Fill the board with empty space
    displayBoard(board); //Display the current board to the screen
	displayMenu(); //Display the menu to the user

	if(argc == 1){
		while(isRunning == 0){
        	char command,x,space;
	        int row,col;
			displayBoard(board); //Display the current board to the screen
			displayMenu(); //Display the menu to the user

			scanf("%s",&command);
    		
    		//Switch statement to interpret the input
    		switch (command) {
        		case 'a':
                	scanf("%d %d", &row, &col);
					if(row > SIZE || row < 1 || col > SIZE || col < 1){
						printf("Coordinates are out of bounds (They have to be between 1 and 40)");
						break;
					}
            		board[row-1][col-1] = 'X'; //Add cell to the array
            		break;
        		case 'r':
                	scanf("%d %d", &row, &col);
            		if(row > SIZE || row < 1 || col > SIZE || col < 1){
                		printf("Coordinates are out of bounds (They have to be between 1 and 40)");
                		break;
            		}
            		board[row-1][col-1] = ' '; //Remove cell from array
            		break;
        		case 'n':
            		step(board);
            		break;
        		case 'q':
            		isRunning = 2;
            		break;
        		case 'p':
            		isRunning = 1;
            		break;
        		default:
            		printf("You input an invalid letter\n");
            		break;
    		}


		}			
			
				
	
		if(isRunning == 2){
			printf("GoodBye!\n");
			return 0;	
		}	
	} else if(argc ==2) {
		char command;
		int row, col;
		fp = fopen(argv[1],"r");
		if(!fp){
			printf("%s not found\n",argv[1]);	
		}
		while(1){
			fscanf(fp,"%s %d %d",&command,&row,&col);
			if(feof(fp)) break;
			switch(command){
				case 'a':	
            		board[row-1][col-1] = 'X'; //Add cell to the array
					break;
				case 'r':
            		board[row-1][col-1] = ' '; //Add cell to the array
					break;
				case 'n':
					step(board);
					break;
			} 
				

		}
		displayBoard(board);	
	} else {
		printf("Invalid number of arguments\n");	
	}


	//Run simulation
	while(1){
		step(board);
		displayBoard(board);
		usleep(sleepTime);	
	}



    return 0;
}
