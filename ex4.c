#include <stdio.h>
#define stackLength 50
int stack[stackLength] = {0};
int topIndex = -1;
void push(int num){    
	if (topIndex > (stackLength - 1)){        
		printf("Stack is Full!\n");        
		return;    
	}    
	topIndex++;    
	stack[topIndex] = num;
}

void pop(){    
	if (topIndex == -1) {        
		return;    
	}    
	topIndex--;
}

void display(){    
	int i;    
	if (topIndex == -1){        
		printf("Stack is Empty!\n");        
		return;    
	}    
	for (i=0;i<=topIndex;i++){        
		printf("%d\n",stack[i]);    
	}    
	printf("=======================================\n");
}

int main() {    
	push(15);    
	push(6);    
	push(27);    
	display();    
	pop();    
	display();    
	pop();    
	display();    
	pop();    
	display();    
	push(0);    
	display();    
	return 0;
}
