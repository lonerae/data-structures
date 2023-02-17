#include <stdio.h>
#include <stdlib.h>
#include "helpers/expression_stack.h"


/*global variable that holds the dimension of the user's array*/
int dim;

/* a pointer to a vector of pointers each one of which point to the
 lower and upper bound indexes of the user's array */
int** boundsPtr;
int base = 100;
int length = 6;


int getUserInput(){
    int i,j;

    printf("Type the array's dimension: ");
    scanf("%d", &dim);

    /* user input validation */
    if (dim <= 0){
        printf("Invalid input. \n");
        /* error exit code */
        return 0;
    }
    else{
        /* dynamic allocation of the pointer (the rows of the 2D array representation)*/
        boundsPtr = (int**)malloc(sizeof(int)*dim);
        for(i=0;i<dim;i++){
            /* dynamic allocation of a pointer (the columns of the 2D array representation)*/
            boundsPtr[i] = (int*)malloc(sizeof(int)*2);
            for (j=0;j<2;j++){
                printf("Type index %d of dimension %d\n",j+1,i+1);
                scanf("%d",&boundsPtr[i][j]);
                if (j%2 == 1){
                    /* user input validation */
                    if (boundsPtr[i][j-1]>boundsPtr[i][j]){
                        printf("invalid input.\n");
                        return 0;
                    }
                }
            }


        }
        return 1;
    }
}

/* calculate all the (dimension + 1) coefficients of the given element of the array */
int findCoefficients(int coefficients[]) {
    int j;
    *(coefficients+dim) = length;
    for (j=dim-1;j>0;j--){
        *(coefficients+j)=(boundsPtr[j][1] - boundsPtr[j][0] + 1) * *(coefficients+j+1);
    }

    int sum = base;
    for (j=1;j<=dim;j++){
        sum-=*(coefficients+j) * boundsPtr[j-1][0];
    }
    *(coefficients+0) = sum;
    return sum;
}

/* calculate and print the exact memory address of the given element of the array */
void findAddress(int sum, int coefficients[], int* ptr){
    int j;
    for (j=0;j<dim;j++){
        sum+=*(coefficients+j+1) * *(ptr +j);
    }
    printf("Address of element ( ");
    for( j=0; j<dim; j++){
        printf("%d ",*(ptr+j));
    }
    printf(") is ");
    printf("%d ",sum);
}

/* find recursively the valid indexes of all the elements of the user's array and calculate their address*/
void findIndexes(int* ptr, int index){

    int i,sum;
    int coefficients[dim+1];

    for(i=boundsPtr[index][0];i<=boundsPtr[index][1];i++){
        push(i);
        if (index==dim-1) {
            sum = findCoefficients(coefficients);
            findAddress(sum,coefficients,ptr);
            printf("\n");

        } else{
            /* find the next sequence of indexes */
            findIndexes(ptr,index +1);
        }
        pop();
    }
}

int main() {
    int i;
    /* a stack that contains a vector of indexes */
    int *ptr = getStack();

    if (getUserInput()){
        for (i=0; i<dim; i++) {
            printf("===Row %d===\n",i+1);
            printf("Lower bound: %d, Upper bound: %d\n",boundsPtr[i][0],boundsPtr[i][1]);
            printf("\n");
        }
        /* initialize recursion */
        findIndexes(ptr,0);
    }
    return 0;
}
