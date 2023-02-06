/* to kalo me auton ton tropo einai oti tha paizei gia opoiodipote expression
 * alla tha synantisei provlima ans to expression emperiexontai oi arithmoi 42, 43, 45, 47
 * pou einai ta adistoixa (*, +, -, /) sto ASCII */

#include <stdio.h>

#define stack_size 3
#define N 9

int stack[stack_size];
int top = -1;

void print_stack (int x) {
    int i;
    printf("%d. Stack contains: ", x+1);
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
    int expression[N] = {10, 3, '-', 8, 3, '+', '*', 2, '+'};
    int i, temp1, temp2, result;
    int sum = (int) ('+');
    int minus = (int) ('-');
    int mult = (int) ('*');
    int div = (int) ('/');

    for(i=0; i<N; i++) {
        if (expression[i] == sum) {
            temp1 = pop();
            temp2 = pop();
            result = temp1 + temp2;
            push(result);
        }
        else if (expression[i] == minus) {
            temp1 = pop();
            temp2 = pop();
            result = temp2 - temp1;
            push(result);
        }
        else if (expression[i] == mult) {
            temp1 = pop();
            temp2 = pop();
            result = temp1 * temp2;
            push(result);
        } else if (expression[i] == div) {
            temp1 = pop();
            temp2 = pop();
            result = temp1 / temp2;
            push(result);
        }
        else {
            push(expression[i]);
        }
        print_stack(i);
    }

    return 0;
};