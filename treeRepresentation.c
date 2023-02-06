#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 50

void clean(char *e, char *ans) {
	int i = 0;
	int j = 0;
	while (i < MAX_LENGTH) {
		if (!isspace(*(e+i))) {
			if (*(e+i) == '(' || *(e+i) == '{' || *(e+i) == '[') {
				*(ans+j) = '(';
			} else if (*(e+i) == ')' || *(e+i) == '}' || *(e+i) == ']') {
				*(ans+j) = ')';
			} else  {
				*(ans+j) = *(e+i);
			}
			j++;
		}		
		i++;
	}
}

struct treeNode {
	char operator;
	int value;
	
	struct treeNode *above;
	struct treeNode *left;
	struct treeNode *right;
};

struct treeNode *root;

void findLeft(char *e, char *left, int *leftFlag) {
	int i = 0;
	int length = strlen(e); 
	if (*(e+i) == '(') {
		int count = 0;
		int j = 0;
		i++;
		while (*(e+i) != ')' || count != 0) {
			*(left+j) = *(e+i);
			if (*(e+i) == '(') {
				count++;
			} else if (*(e+i) == ')') {
				count--;
			}	
			j++;
			i++;
		}
		*(left+j) = '\0';
		i++;
	} else {
		int j = 0;
		while (isdigit(*(e+i))) {
			*(left+j) = *(e+i);
			j++;
			i++;
		}
		*(left+j) = '\0';
		*leftFlag = 1;
	}
	//printf("(SUBTREE) LEFT: %s\n",left);
}

void simplify(char *right, int *rightFlag) {
	int l = strlen(right);
	if (*right == '(' && *(right+l-1) == ')') {
		for (int i=1; i<l-1;i++) {
			*(right+i-1) = *(right+i);
		}		
		*(right+l-2) = '\0';
	}
}

void findRight(char *e, char *right, int startIndex, int *rightFlag) {
	int z = 0;
	int i = startIndex;
	while (*(e+i) != '\0') {
		if (!isdigit(*(e+i))) {
			*rightFlag = 0;
		}
		*(right+z) = *(e+i);
		i++;
		z++;
	}
	*(right+z) = '\0';
	simplify(right,rightFlag);
	//printf("(SUBTREE) RIGHT: %s\n",right);
}

struct treeNode *transform(char *e) {
	int length = strlen(e); 
	char left[length];
	char right[length];
	int *leftFlag = (int *) malloc(sizeof(int));
	int *rightFlag = (int *) malloc(sizeof(int));
	*leftFlag = 0; *rightFlag = 1;
	findLeft(e,left,leftFlag);

	struct treeNode *parent = (struct treeNode*) malloc(sizeof(struct treeNode));	
	struct treeNode *leftChild = (struct treeNode*) malloc(sizeof(struct treeNode));
	struct treeNode *rightChild = (struct treeNode*) malloc(sizeof(struct treeNode));
	if (root == NULL) {
		root = (struct treeNode*) malloc(sizeof(struct treeNode));
		root = parent;
	}
	
	if (*leftFlag) {
		parent->operator = *(e+strlen(left));
		leftChild->value = atoi(left);
		//printf("(LEAF) Left: %d\n",leftChild->value);
		
		findRight(e,right,strlen(left)+1,rightFlag);
	} else {
		parent->operator = *(e+strlen(left)+2);
		leftChild = transform(left);
		
		findRight(e,right,strlen(left)+3,rightFlag);
	}
	
	
	
	parent->left = leftChild;	
	leftChild->above = parent;
	
	if (*rightFlag) {
		rightChild->value = atoi(right);
		//printf("(LEAF) Right: %d\n",rightChild->value);
	} else {
		rightChild = transform(right);
	}
	parent->right = rightChild;
	rightChild->above = parent;
	
	
	
	return parent;
}

void traverseTree(struct treeNode* node) {
	if (node->left != NULL) {
		traverseTree(node->left);
	} else {
		printf("%d ",node->value);
		return;
	}
	
	printf("%c ",node->operator);
	
	if (node->right != NULL) {
		traverseTree(node->right);
	} else {
		printf("%d ",node->value);
		return;
	}
}

int main() {
	char e[MAX_LENGTH];
	char ans[MAX_LENGTH];
	printf("Write an arithmetic expression: \n");
	fgets(e,MAX_LENGTH,stdin);
	
	clean(e,ans);
	//printf("New form: %s\n",ans);
	transform(ans);
	traverseTree(root);
	printf("\n");
	
	return 0;
}
