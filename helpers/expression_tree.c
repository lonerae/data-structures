#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "expression_tree.h"

struct treeNode *root;

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

void simplify(char *expression) {
	int length = strlen(expression);
	
	if (*(expression+0) == '(' && *(expression+length-1) == ')') {
		for (int expressionIndex=1; expressionIndex<length-1;expressionIndex++) {
			*(expression+expressionIndex-1) = *(expression+expressionIndex);
		}
		*(expression+length-2) = '\0';
	}	
}

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

struct treeNode *makeTree(char *expression) {
	int length = strlen(expression);

	char left[length];
	int *leftFlag = (int *) malloc(sizeof(int));
	*leftFlag = 1;

	char right[length];
	int *rightFlag = (int *) malloc(sizeof(int));
	*rightFlag = 1;

	struct treeNode *parent = (struct treeNode*) malloc(sizeof(struct treeNode));
	// makes certain that the root is set on the first and only the first call of the function
	// and the outer parentheses are removed
	if (root == NULL) {
		root = (struct treeNode*) malloc(sizeof(struct treeNode));
		root = parent;
		simplify(expression);
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
		leftChild = makeTree(left);

		findRight(expression,right,strlen(left)+3,rightFlag);
	}
	parent->left = leftChild;
	leftChild->above = parent;

	if (*rightFlag) {
		strcpy(rightChild->value,right);
	} else {
		rightChild = makeTree(right);
	}
	parent->right = rightChild;
	rightChild->above = parent;

	return parent;
}

int part = 0;
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

void traverseFromRoot(char result[][MAX_EXPRESSION_LENGTH]) {
	traverseTree(root,result);
}
