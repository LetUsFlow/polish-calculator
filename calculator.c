#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"

int main(int argc, char *argv[]) {

    stack_t stack = {NULL};
    stack_push(&stack, 15);
    stack_push(&stack, 8);
    stack_push(&stack, 3);
    print_stack(&stack);
    printf("%f\n", stack_pop(&stack));
    printf("%f\n", stack_pop(&stack));
    printf("%f\n", stack_pop(&stack));
    double last = stack_pop(&stack);
    printf("%f, isnan(last): %d\n", last, isnan(last));

    return EXIT_SUCCESS;
}
