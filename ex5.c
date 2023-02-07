#include <stdio.h>
#include <stdlib.h>

struct Node {    
	int number;    
	struct Node* next;
};

struct Node* head;

void push(int num, int i) {
	struct Node* tmp;    
	tmp = (struct Node*)malloc(sizeof (struct Node));    
	tmp->number = num;    
	if (head == NULL){        
		head = tmp;        
		head->next = NULL;    
	}    else {        
		tmp->next = head;        
		head=tmp;    
	}
}

void pop(){    
	if (head != NULL) {        
		head = head->next;    
	}
}

void display(){    
	struct Node* tmp;    
	if (head == NULL) {        
		return;    
	}   
       	tmp = head;   
       	while (tmp != NULL){      
	       printf("%d\n",tmp->number);       
	       tmp = tmp->next;    
	}
}

int main() {
    push(8, 0);
    push(9, 0);
    push(10, 0);
	display();    
	printf("========================================================\n");    
	pop();    
	display();    
	return 0;
}
