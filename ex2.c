#include <stdio.h>

/* array which stores the lower and upper bound indexes of a given multidimensional array */
int bounds[4][2]={{1,2},{1,3},{3,3},{1,2}};

/* array's dimension calculation */
int dim = sizeof(bounds)/(sizeof(int)*2);
int base = 100;
int length = 6;

/* calculate all the (dimension + 1) coefficients of the given element of the array */
int findCoefficients(int coefficients[]) {
	*(coefficients+dim) = length;
	for (int j=dim-1;j>0;j--){        
		*(coefficients+j)=(bounds[j][1] - bounds[j][0] + 1) * *(coefficients+j+1);    
	}    

	int sum = base;    
	for (int j=1;j<=dim;j++){        
		sum-=*(coefficients+j) * bounds[j-1][0];    
	}    
	*(coefficients+0) = sum;   
	return sum;
}

/* calculate the exact memory address of the given element of the array */
void findAddress(int sum, int coefficients[], int indexes[]){

	for (int j=0;j<dim;j++){
		sum+=*(coefficients+j+1) * indexes[j];
	}
	printf("Address of element (%d, %d, %d, %d) is %d\n",indexes[0],indexes[1],indexes[2],indexes[3],sum);
}

int main() {       
	int sum,i,j,k,l;
	int coefficients[dim+1];
    /* vector which stores the indexes of an element */
    int indexes[dim];

	for (int i =0; i<4; i++) {
		printf("===Row %d===\n",i+1); 
		printf("Lower bound: %d, Upper bound: %d\n",bounds[i][0],bounds[i][1]);
		printf("\n");
	}

    /* iterate through every element of the array and calculate its address */
    for (i=bounds[0][0];i<=bounds[0][1]; i++) {
        indexes[0] = i;
        for (j = bounds[1][0]; j <= bounds[1][1]; j++) {
            indexes[1] = j;
            for (k = bounds[2][0]; k <= bounds[2][1]; k++) {
                indexes[2] = k;
                for (l = bounds[3][0]; l <= bounds[3][1]; l++) {
                    indexes[3] = l;
                    sum = findCoefficients(coefficients);
                    findAddress(sum,coefficients,indexes);
                }
            }
        }
    }
	return 0;
}
