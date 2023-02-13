#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "helpers/expression_tree.h"
#include "helpers/expression_stack.h"

char evaluatedExpression[MAX_EXPRESSION_LENGTH][MAX_EXPRESSION_LENGTH];

int main() {
	
	char expression[MAX_EXPRESSION_LENGTH];
	printf("GIVE AN ARITHMETIC EXPRESSION: ");
	fgets(expression,MAX_EXPRESSION_LENGTH,stdin);
	printf("\n");
	
	char result[MAX_EXPRESSION_LENGTH];
	cleanExpression(expression,result);
	printf("CLEAN FORM OF EXPRESSION: %s\n",result);
	printf("\n");
	
	makeTree(result);
	traverseFromRoot(evaluatedExpression);
	int length = sizeof(evaluatedExpression) / (MAX_EXPRESSION_LENGTH * sizeof(char));
	printf("TREE FORM OF EXPRESSION (POST-ORDER): ");
	for (int i=0; i<length; i++) {
		printf("%s ", evaluatedExpression[i]);
	}
	printf("\n");

	printf("===STACK RESULT EVALUATION===\n");
	evaluateResult(evaluatedExpression);
	
	return 0;
}
