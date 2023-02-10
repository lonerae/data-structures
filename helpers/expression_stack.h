#ifndef EXPRESSION_STACK_H
#define EXPRESSION_STACK_H

#include "constants.h"

void print_stack (int x);
void push(int number);
int pop ();
void evaluateResult(char evaluatedExpression[MAX_EXPRESSION_LENGTH][MAX_EXPRESSION_LENGTH]);

#endif
