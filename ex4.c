#include <stdio.h>
#include <stdlib.h>

/* Initializes Stack */
#define stackLength 20
int stack[stackLength] = {0};
int topIndex = -1;

/* Declares Stack's Functions */
void push(int num) {
    /* Evaluates if stack is full by checking whether the top matches the stack's length */
	if (topIndex > (stackLength - 1)){
        printf("Process failed. Stack if full.");
	}
    /* When stack isn't full, the top index of the stack advances by one with num as its data */
    else {
        topIndex++;
        stack[topIndex] = num;
        printf("\nNumber added!");
    }
}

void pop() {
    /* Evaluates if stack is empty by checking whether the top matches its initial value */
    if (topIndex == -1) {
        printf("\nNothing to remove. Stack is empty.");
	}
    /* When stack isn't empty, the top index of the stack lowers by one and so the stack's last inserted data is removed */
    else {
        topIndex--;
        printf("\nNumber removed!");
    }
}

void display() {
	int i;
    /* Evaluates if stack is empty by checking whether the top matches its initial value and prints relevant message */
    if (topIndex == -1) {
		printf("\nNothing to display. Stack is empty.");
		return;    
	}
    /* When stack isn't empty, it loops through all the stack's elements to print them */
    else {
        printf("\nStack contains: ");
        for (i=0;i<=topIndex;i++) {
            printf("%d  ",stack[i]);
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
