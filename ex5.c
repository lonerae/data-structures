#include <stdio.h>
#include <stdlib.h>

/* Declares a linked list's node structure containing a data part and its pointer with the address of the next node  */
struct Node {    
	int number;
	struct Node* next;
};

struct Node* head;

/* Declares Stack's Functions */
void push(int num) {
    struct Node* tmp;
    /* allocates memory dynamically for any new nodes that will be added */
	tmp = (struct Node*)malloc(sizeof (struct Node));
	/* data part of new node contains the value of int num */
    tmp->number = num;
    /* Evaluates if stack is empty by checking whether the head equals NULL.
     * If so, the head points to the new node
     * And the head's next points to the address of NULL */
    if (head == NULL) {
		head = tmp;
		head->next = NULL;
	}
    /* When not empty, the new node points to the address that head points to
     * and then head points to the new node */
    else {
		tmp->next = head;
		head = tmp;
	}
    printf("\nNumber added!");
}

void pop()  {
    /* Evaluates if stack isn't empty by checking whether the head doesn't equal NULL. */
    /* Head points to the next node and current one is removed */
    if (head != NULL) {
            head = head->next;
            printf("\nNumber removed!");
    }
    /* When head equals NULL and stack is empty, prints relevant message. */
    else {
        printf("\nNothing to remove. Stack is empty.");
    }
}

void display()  {
struct Node* tmp;
    /* Evaluates if stack is empty by checking whether the head equals NULL and prints relevant message. */
    if (head == NULL) {
        printf("\nNothing to display. Stack is empty.");
        return;
        }
    /* When opposite, loops through the list until its end and prints all its elements
    * each time moving forward by pointing to the next element */
    else {
        printf("\nStack contains: ");
        tmp = head;
        while (tmp != NULL){
            printf("%d  ",tmp->number);
            tmp = tmp->next;
            }
        }
    }

int main() {
    int choice, number;

    /* Presents a menu that requests user input in the form of an endless loop that will stop when exit option 4 is selected*/
    while(1) {
        printf("------------------------------------\n");
        printf("Stack menu: \n");
        printf("1. Add an integer number to the stack\n");
        printf("2. Remove a number from the stack\n");
        printf("3. View stack's contents\n");
        printf("4. Exit the program\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

    switch(choice) {
        case 1:
            printf("Enter number: ");
            scanf("%d", &number);
            push(number);
            break;
        case 2:
            pop();
            break;
        case 3:
            display();
            break;
        case 4:
            printf("Bye!");
            exit(0);
        default:
            printf("Invalid choice, please try again.");
        }
    printf("\n\n");
    }
}
