#include <stdio.h>
#include <stdlib.h>

#define stackLength 20
int stack[stackLength] = {0};
int topIndex = -1;
void push(int num) {
	if (topIndex > (stackLength - 1)){
        printf("Process failed. Stack if full.");
	}
    else {
        topIndex++;
        stack[topIndex] = num;
        printf("\nNumber added!");;
    }
}

void pop(){
	if (topIndex == -1) {
        printf("Process failed. Stack is empty.");
	}
    else {
        topIndex--;
        printf("\nNumber removed!");
    }
}

void display(){    
	int i;    
	if (topIndex == -1){        
		printf("Nothing to display. Stack is empty.");
		return;    
	}
    else {
        printf("Stack contains: ");
        for (i=0;i<=topIndex;i++) {
            printf("%d  ",stack[i]);
        }
    }
}

int main() {
    int choice, number;

    while(1) {
        printf("------------------------------------\n");
        printf("Stack menu: \n");
        printf("1. Add a number to the stack\n");
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
