#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "expression_tree.h"

struct treeNode *root;

/**
* Returns a numeric expression where all white spaces are trimmed
* and all parentheses, brackets and braces are replaced by parentheses.
*
* Parameters
*	expression - pointer to the initial string
*	result - pointer to the result
*/
void cleanExpression(char *expression, char *result) {
	int expressionIndex = 0;
	int resultIndex = 0;

	while (expressionIndex < MAX_EXPRESSION_LENGTH) {
		if (!isspace(*(expression+expressionIndex))) {
			if (*(expression+expressionIndex) == '(' || *(expression+expressionIndex) == '{' || *(expression+expressionIndex) == '[') {
				*(result+resultIndex) = '(';
			} else if (*(expression+expressionIndex) == ')' || *(expression+expressionIndex) == '}' || *(expression+expressionIndex) == ']') {
				*(result+resultIndex) = ')';
			} else  {
				*(result+resultIndex) = *(expression+expressionIndex);
			}
			resultIndex++;
		}
		expressionIndex++;
	}
}

/**
* Removes the outer parentheses of an expression.
*
* Parameters
*	expression - pointer to the given expression
*
* WARNING: TREATS THE EXPRESSION (STRING i.e. character array) AS A MUTABLE OBJECT
*/
void simplify(char *expression) {
	int length = strlen(expression);
	
	if (*(expression+0) == '(' && *(expression+length-1) == ')') {
		for (int expressionIndex=1; expressionIndex<length-1;expressionIndex++) {
			*(expression+expressionIndex-1) = *(expression+expressionIndex);
		}
		*(expression+length-2) = '\0';
	}	
}

/**
* Returns the left operand of a numeric expression and
* informs whether it was an expression or a number.
* e.g.
*	if expression pointed to [1-(2*5)]+3-[(2-4)/3],
*	left would point to 1-(2*5) and leftFlag to 0
*
* Parameters
*	expression - pointer to the expression
*	left - pointer to the left operand
*	leftFlag - pointer to 1 if left is just a number, otherwise to 0
*/
void findLeft(char *expression, char *left, int *leftFlag) {
	int expressionIndex = 0;
	int leftIndex = 0;
	int length = strlen(expression);

	if (*(expression+expressionIndex) == '(') {
		int nestedParentheses = 0;
		expressionIndex++;
		while (*(expression+expressionIndex) != ')' || nestedParentheses != 0) {
			*(left+leftIndex) = *(expression+expressionIndex);
			if (*(expression+expressionIndex) == '(') {
				nestedParentheses++;
			} else if (*(expression+expressionIndex) == ')') {
				nestedParentheses--;
			}
			leftIndex++;
			expressionIndex++;
		}
		*(left+leftIndex) = '\0';
		*leftFlag = 0;
		expressionIndex++;
	} else {
		while (isdigit(*(expression+expressionIndex))) {
			*(left+leftIndex) = *(expression+expressionIndex);
			leftIndex++;
			expressionIndex++;
		}
		*(left+leftIndex) = '\0';
	}
}

/**
* Returns the right operand of a numeric expression and
* informs whether it was an expression or a number.
* e.g.
*	if expression pointed to [1-(2*5)]+3-[(2-4)/3],
*	right would point to 3-[(2-4)/3] and rightFlag to 0
*
* Parameters
*	expression - pointer to the expression
*	right - pointer to the right operand
*	startIndex - index after which we should evaluate the right operand (depending on left operand length)
*	rightFlag - pointer to 1 if right is just a number, otherwise to 0
*/
void findRight(char *expression, char *right, int startIndex, int *rightFlag) {
	int rightIndex = 0;
	int expressionIndex = startIndex;

	while (*(expression+expressionIndex) != '\0') {
		if (!isdigit(*(expression+expressionIndex))) {
			*rightFlag = 0;
		}
		*(right+rightIndex) = *(expression+expressionIndex);
		expressionIndex++;
		rightIndex++;
	}
	*(right+rightIndex) = '\0';
	simplify(right);
}

/**
* Recursively creates a tree representation of a given expression
*
* Parameters
*	expression - pointer to the expression
*/
struct treeNode *transform(char *expression) {
	int length = strlen(expression);

	char left[length];
	int *leftFlag = (int *) malloc(sizeof(int));
	*leftFlag = 1;

	char right[length];
	int *rightFlag = (int *) malloc(sizeof(int));
	*rightFlag = 1;

	struct treeNode *parent = (struct treeNode*) malloc(sizeof(struct treeNode));
	// makes certain that the root is set on the first and only the first call of the function
	if (root == NULL) {
		root = (struct treeNode*) malloc(sizeof(struct treeNode));
		root = parent;
	}

	struct treeNode *leftChild = (struct treeNode*) malloc(sizeof(struct treeNode));
	struct treeNode *rightChild = (struct treeNode*) malloc(sizeof(struct treeNode));

	findLeft(expression,left,leftFlag);
	if (*leftFlag) {
		parent->value[0] = *(expression+strlen(left)); // operators are characters (just 1B long)
		strcpy(leftChild->value,left);

		findRight(expression,right,strlen(left)+1,rightFlag);
	} else {
		parent->value[0] = *(expression+strlen(left)+2);
		leftChild = transform(left);

		findRight(expression,right,strlen(left)+3,rightFlag);
	}
	parent->left = leftChild;
	leftChild->above = parent;

	if (*rightFlag) {
		strcpy(rightChild->value,right);
	} else {
		rightChild = transform(right);
	}
	parent->right = rightChild;
	rightChild->above = parent;

	return parent;
}

int part = 0;

/**
* Post-order traversal of a subtree and
* insertion to the evaluated expression array.
*
* Parameters
* 	node - the root node of the subtree
*/
void traverseTree(struct treeNode* node, char result[][MAX_EXPRESSION_LENGTH]) {
	if (node->left != NULL) {
		traverseTree(node->left,result);
	} else {
		strcpy(result[part],node->value);
		part++;
		return;
	}

	if (node->right != NULL) {
		traverseTree(node->right,result);
	} else {
		strcpy(result[part],node->value);
		part++;
		return;
	}

	strcpy(result[part],node->value);
	part++;
}

void start(char result[][MAX_EXPRESSION_LENGTH]) {
	traverseTree(root,result);
}
