#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

#include "constants.h"

struct treeNode {
	char value[MAX_DIGIT_NUMBER];

	struct treeNode *above;
	struct treeNode *left;
	struct treeNode *right;
};

void cleanExpression(char *expression, char *result);
void simplify(char *expression);
void findLeft(char *expression, char *left, int *leftFlag);
void findRight(char *expression, char *right, int startIndex, int *rightFlag);
struct treeNode *transform(char *expression);
void traverseTree(struct treeNode* node, char result[][MAX_EXPRESSION_LENGTH]);
void start(char result[][MAX_EXPRESSION_LENGTH]);

#endif
