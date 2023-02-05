#include <stdio.h>

int bounds[4][2]={{1,2},{1,3},{3,3},{1,2}};
int dim = sizeof(bounds)/(sizeof(int)*2);
int base = 100;
int length = 6;
int main() {       
	int sum;    
	int coefficients[dim+1];    
	int indexes[dim];    
	

	for (int i =0; i<4; i++) {
		printf("===Row %d===\n",i+1); 
		printf("Lower bound: %d, Upper bound: %d\n",bounds[i][0],bounds[i][1]);
		printf("\n");
	}

	/*c4 = 6*/
	coefficients[dim] = length;
	
	/*c3 = 12,c2 = 12,c1 = 36*/
	for (int j=dim-1;j>0;j--){        
		coefficients[j]=(bounds[j][1] - bounds[j][0] + 1) * coefficients[j+1];    
	}    

	/*c0 = 10*/
	sum = base;    
	for (int j=1;j<=dim;j++){        
		sum-=coefficients[j] * bounds[j-1][0];    
	}    
	coefficients[0] = sum;   
	

	for (int i = 0; i<5; i++) {
		printf("============\n");
		printf("C%d: %d\n",i,coefficients[i]);
		printf("\n");
	}

	/*-----------------------------------------*/


	for (int j=0;j<dim;j++){        
		printf("Insert index %d: ",j+1);
		scanf("%d",&indexes[j]);
		sum+=coefficients[j+1]*indexes[j];    
		printf("\n");
	}    

	printf("Address of given element is %d\n",sum);

	return 0;
}
