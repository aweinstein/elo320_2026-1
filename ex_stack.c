#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef struct {
    int n; // numero de elementos en el stack
    int data[MAXSIZE];    
} stack;

stack *make_stack(void);
void push(stack *sp, int data);
int pop(stack *sp);
void display_stack(stack *sp);


int main(void)
{
    printf("Stacks basado en arreglos... \n");
    stack *s = NULL;
    int x;
    s = make_stack();
    push(s, 12);
    push(s, 34);
    push(s, 56);
    display_stack(s);
    x = pop(s);
    printf("Sacamos %d del stack\n", x);
    display_stack(s);
    return 0;   
}

stack *make_stack(void)
{
    stack *sp = malloc(sizeof(stack)); // Falta el caso en que malloc retorne NULL
    sp->n = 0;
    return sp;
}

void push(stack *sp, int a)
{
    if(sp->n == MAXSIZE)
        exit(1);  // Pensar en una forma mas elegante para manejar el error
    else
      sp->data[sp->n++] = a;    
}

int pop(stack *sp)
{
    if(sp->n == 0)
        exit(1);
    else
        return sp->data[--(sp->n)];    
}


void display_stack(stack *sp)
{
    int i;
    printf("--------\n");
    for(i = sp->n - 1; i>=0; i--)
        printf("%d\n", sp->data[i]);   
    printf("--------\n"); 
}
