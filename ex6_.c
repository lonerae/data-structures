#include <stdio.h>

#define stack_size 3

int stack[stack_size];
int top = -1;

void print_stack (int x) {
    int i;
    printf("Stack contains: ");
    for (i=0; i<stack_size; i++) {
        printf(" %d |", stack[i]);
    }
    printf("\n");
};
void push(int number) {
    if (top>(stack_size-1)){
        printf("Stack is Full!\n");
        return;
    }
    else {
        top++;
        stack[top] = number;
    }
}
int pop () {
    if (top == -1) {
        return 0;
    }
    else {
        int number = stack[top];
        stack[top] = 0;
        top--;
        return number;
    }
}

int main () {

    int i, temp1, temp2;
    int res1, res2, res3, result;

    push(10);
    print_stack(i);
    push(3);
    print_stack(i);
    temp1 = pop();
    temp2 = pop();
    res1 = temp2 - temp1;
    push(res1);
    print_stack(i);
    push(8);
    push(3);
    print_stack(i);
    temp1 = pop();
    temp2 = pop();
    res2 = temp1 + temp2;
    push(res2);
    print_stack(i);
    res1 = pop();
    res2 = pop();
    res3 = res1 * res2;
    push(res3);
    print_stack(i);
    push(2);
    temp1 = pop();
    temp2 = pop();
    result = temp1 + temp2;
    push(result);
    print_stack(i);

    return 0;
}