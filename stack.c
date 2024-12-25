#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "stack.h"

void stack_push(stack_t *stack, double value) {
    struct llnode *newhead = malloc(sizeof(struct llnode));
    newhead->value = value;
    newhead->next = stack->head;
    stack->head = newhead;
}

double stack_pop(stack_t *stack) {
    struct llnode *oldhead = stack->head;
    if (oldhead != NULL) {
        stack->head = oldhead->next;
        double value = oldhead->value;
        free(oldhead);
        return value;
    }
    return NAN;
}

void print_stack(stack_t *stack) {
    printf("stack: [");
    struct llnode *node = stack->head;
    int first = 1;
    while (node != NULL) {
        if (!first) {
            printf(", ");
        } else {
            first = 0;
        }
        printf("%f", node->value);
        node = node->next;
    }
    printf("]\n");
}
