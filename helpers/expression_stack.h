#ifndef EXPRESSION_STACK_H
#define EXPRESSION_STACK_H

#include "constants.h"

void print_stack (int x);
int* getStack();
void push(int number);
int pop ();

/**
* Loops through each row to identify when string is digit with function isdigit
* and repeats push or pop functions based on that
* if a string is a digit, it converts the string to digit with atoi and pushes the digit to the stack
* if not, it pops the last two digits and calculates their result. 
*/
void evaluateResult(char evaluatedExpression[MAX_EXPRESSION_LENGTH][MAX_EXPRESSION_LENGTH]);

#endif
