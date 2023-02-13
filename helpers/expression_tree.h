#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

#include "constants.h"

struct treeNode {
	char value[MAX_DIGIT_NUMBER];

	struct treeNode *above;
	struct treeNode *left;
	struct treeNode *right;
};

/**
* Returns a numeric expression where all white spaces are trimmed
* and all parentheses, brackets and braces are replaced by parentheses.
*
* Parameters
*	expression - pointer to the initial string
*	result - pointer to the result
*/
void cleanExpression(char *expression, char *result);

/**
* Removes the outer parentheses of an expression.
*
* Parameters
*	expression - pointer to the given expression
*
* WARNING: TREATS THE EXPRESSION (STRING i.e. character array) AS A MUTABLE OBJECT
*/
void simplify(char *expression);

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
void findLeft(char *expression, char *left, int *leftFlag);

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
void findRight(char *expression, char *right, int startIndex, int *rightFlag);

/**
* Recursively creates a tree representation of a given expression
*
* Parameters
*	expression - pointer to the expression
*/
struct treeNode *makeTree(char *expression);

/**
* Post-order traversal of a subtree and
* insertion to the evaluated expression array.
*
* Parameters
* 	node - the root node of the subtree
*/
void traverseTree(struct treeNode* node, char result[][MAX_EXPRESSION_LENGTH]);

void traverseFromRoot(char result[][MAX_EXPRESSION_LENGTH]);

#endif
