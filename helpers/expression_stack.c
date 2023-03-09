#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "expression_stack.h"

int stack[STACK_SIZE];
int top = -1;

void print_stack (int x) {
	int i;
	printf("%d. Stack contains: ", x+1);
	for (i=0; i<STACK_SIZE; i++) {
		printf(" %d |", stack[i]);
	}
	printf("\n");
}

void push(int number) {
	if (top>(STACK_SIZE-1)){
		printf("Stack is Full!\n");
		return;	
	} else {
		top++;
		stack[top] = number;
	}
}

int pop () {
	if (top == -1) {
		return 0;
	} else {
		int number = stack[top];
		stack[top] = 0;
		top--;
		return number;
    	}
}

void evaluateResult(char evaluatedExpression[MAX_EXPRESSION_LENGTH][MAX_EXPRESSION_LENGTH]) {
	int digit, j;
	int temp1, temp2;
	int res;

	for (j=0; j<MAX_EXPRESSION_LENGTH; j++) {
		if (isdigit(evaluatedExpression[j][0])) {
		   digit = atoi(evaluatedExpression[j]);
		   push(digit);
		}
		else {
			if (evaluatedExpression[j][0] == '+') {
				temp1 = pop();
				temp2 = pop();
				res = temp1 + temp2;
				push(res);
			} else if (evaluatedExpression[j][0] == '-') {
				temp1 = pop();
				temp2 = pop();
				res = temp2 - temp1;
				push(res);
			} else if (evaluatedExpression[j][0] == '*') {
				temp1 = pop();
				temp2 = pop();
				res = temp1 * temp2;
				push(res);
			} else if (evaluatedExpression[j][0] == '/') {
				temp1 = pop();
				temp2 = pop();
				res = temp1 / temp2;
				push(res);
			} else if (evaluatedExpression[j][0] == '\0') {
				break;
			}
		}
		print_stack(j);
	}
}	


