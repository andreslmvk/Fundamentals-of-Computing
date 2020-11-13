/* Andres Lacayo
 * Fundamentals of Computing 
 * addup.c
 */

#include<stdio.h>
#include<stdlib.h>

//Function Prototypes

int main(int argc, char *argv[]) {
    int a,b;
    if(argc == 1){
        printf("Input two integers:");
        scanf("%d",&a);
        scanf("%d",&b);
    } else if (argc == 3) {
        a = atoi(argv[1]);
        b = atoi(argv[2]);
    } else {
        printf("You input an incorrect number of arguments\n");
        return 1;
    }

    printf("\nThe sum of %d and %d is %d\n",a,b,a+b);

    return 0;
}

//Function Definitions