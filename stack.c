#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "stack.h"

void stack_push(stack_t *stack, double value) {
    struct llnode *newhead = malloc(sizeof(struct llnode));
    newhead->value = value;
    newhead->next = stack->top;
    stack->top = newhead;
}

double stack_pop(stack_t *stack) {
    struct llnode *oldhead = stack->top;
    if (oldhead != NULL) {
        stack->top = oldhead->next;
        double value = oldhead->value;
        free(oldhead);
        return value;
    }
    return NAN;
}

void print_stack(stack_t *stack) {
    printf("stack: [");
    struct llnode *node = stack->top;
    while (node != NULL) {
        printf("%f", node->value);
        if (node->next != NULL) {
            printf(", ");
        }
        node = node->next;
    }
    printf("]\n");
}
