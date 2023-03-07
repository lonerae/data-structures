#include <stdio.h>

void update(float S[], float c, int i) {
	*(S+i) = c;
}

void retrieve(float S[], float *c, int i) {
	*c = S[i];
}

int main() {
	float A[10];
	float B[10];
	float C[10];
	
	float entry;
	float retrievedB,retrievedC;
	
	for (int i = 0; i<10; i++) {
		printf("Give element %d of B: ",i+1);
		scanf("%f",&entry);
		update(B,entry,i);
		printf("Give element %d of C: ",i+1);
		scanf("%f",&entry);
		update(C,entry,i);

		retrieve(B,&retrievedB,i);
		retrieve(C,&retrievedC,i);
		update(A,retrievedB+retrievedC,i);		
	}

	float retrievedA;
	for (int i = 0; i<10; i++) {
		retrieve(A, &retrievedA, i);
		printf("Element %d of A:=B+C is %f\n",i+1,retrievedA);
	}
	  
	return 0;
}
