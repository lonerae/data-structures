#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define base 100
#define length 6

/*global variable that holds the dimension of the user's array*/
int dim;

/* a pointer to a vector of pointers each one of which point to the
 lower and upper bound indexes of the user's array */
int** boundsPtr;

/* 2D array that will store all valid coordinates*/
int** indexes;

bool getUserInput();
int findTotal();
void findIndexes(int guide, int temp[]);
void findCoefficients(int coefficients[]);
void findAddress(int total, int coefficients[]);

int main() {
    if (getUserInput()){
        for (int i=0; i<dim; i++) {
            printf("===Row %d===\n",i+1);
            printf("Lower bound: %d, Upper bound: %d\n",boundsPtr[i][0],boundsPtr[i][1]);
            printf("\n");
        }
	
	int total = findTotal();
	
        /* initialize recursion */
        int coefficients[dim+1];
	findCoefficients(coefficients);

	indexes = (int**) malloc(sizeof(int) * total * dim);
	for (int i = 0; i < total; i++) {
		indexes[i] = (int*) malloc(sizeof(int) * dim);
	};
	int temp[dim];

        findIndexes(0, temp);
        findAddress(total, coefficients);
    }
    return 0;
}

bool getUserInput(){
    int i,j;

    printf("Type the array's dimension: ");
    scanf("%d", &dim);

    /* user input validation */
    if (dim <= 0){
        printf("Invalid input. \n");
        return false;
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
                        return false;
                    }
                }
            }


        }
        return true;
    }
}

/* find total number of elements of multidimensional array */
int findTotal() {
	int total = 1;
	for (int i = 0; i < dim; i++) {
		total *= (boundsPtr[i][1] - boundsPtr[i][0] + 1);
	}
	return total;
}

/* find recursively the valid indexes of all the elements of the user's array and calculate their address*/
int count = 0; // global counter for entries in indexes, to avoid unexpected behaviour during recursion
void findIndexes(int guide, int temp[]) {
	for (int i = boundsPtr[guide][0]; i <= boundsPtr[guide][1]; i++) {
		temp[guide] = i;
		if (guide == dim - 1) {
			for (int j = 0; j < dim; j++) {
				indexes[count][j] = temp[j];
			}
			count++;
		} else {
			findIndexes(guide+1, temp);
		}
	}
}

/* calculate all the (dimension + 1) coefficients of the given element of the array */
void findCoefficients(int coefficients[]) {
	coefficients[dim] = length;
	
	for (int i = dim - 1; i > 0; i--) {
		coefficients[i] = (boundsPtr[i][1] - boundsPtr[i][0] + 1) * coefficients[i+1];
	}
	
	coefficients[0] = base;
	for (int i = 0; i < dim; i++) {
		coefficients[0] -= coefficients[i+1] * boundsPtr[i][0];
	}
}

/* calculate and print the exact memory address of the given element of the array */
void findAddress(int total, int coefficients[]) {
	int addr;
	for (int i = 0; i < total; i++) {
		printf("Address of element ( ");
		addr = coefficients[0];
		for (int j = 0; j < dim; j++) {
			printf("%d ", indexes[i][j]); 
			addr += coefficients[j + 1] * indexes[i][j];
		}
		printf(") is %d\n", addr);
	}
}
