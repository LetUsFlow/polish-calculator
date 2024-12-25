#ifndef LINKEDLIST
#define LINKEDLIST

struct llnode {
    double value;
    struct llnode *next;
};

typedef struct {
    struct llnode *head;
} stack_t;

void stack_push(stack_t *stack, double value);
double stack_pop(stack_t *stack);
void print_stack(stack_t *stack);

#endif
