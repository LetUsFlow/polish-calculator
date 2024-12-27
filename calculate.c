#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include "stack.h"

void malformed_exit(char *err) {
    fprintf(stderr, "%s\nMalformed input! Quitting.\n", err);
    exit(EXIT_FAILURE);
}

void execute_math_operation(stack_t *stack, char operation) {
    double b = stack_pop(stack);
    double a = stack_pop(stack);
    if (isnan(a) || isnan(b)) {
        malformed_exit("At least one input number is missing!");
    }
    double res;
    switch (operation) {
    case '+':
        res = a + b;
        break;
    case '-':
        res = a - b;
        break;
    case '/':
        res = a / b;
        break;
    case '*':
        res = a * b;
        break;
    case '%':
        res = fmod(a, b);
        break;
    default:
        malformed_exit("Could not find correct math operation!");
        break;
    }
    stack_push(stack, res);
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: %s FILE\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *in_fp, *tmp_fp;
    char *line = NULL;
    char *input_file = argv[1];
    size_t len = 0;

    in_fp = fopen(input_file, "r");
    if (in_fp == NULL) {
        perror("Could not read input file");
        return EXIT_FAILURE;
    }

    tmp_fp = tmpfile();
    if (tmp_fp == NULL) {
        perror("Could not open tmpfile");
        return EXIT_FAILURE;
    }

    while (getline(&line, &len, in_fp) != -1) {

        stack_t stack = {NULL};
        char *token = strtok(line, " ");

        while (token != NULL) {
            char *endptr;

            size_t len = strlen(token);
            if (len > 0 && token[len - 1] == '\n') {
                token[len - 1] = '\0'; // remove newline char
                if (len > 1 && token[len - 2] == '\r') {
                    token[len - 2] = '\0'; // Remove carriage return
                }
            }

            double value = strtod(token, &endptr);
            //printf("value: %f\n", value);

            if (*endptr != '\0') {
                if (value != 0 || endptr != token || strlen(endptr) > 1) {
                    //printf("strlen(endptr): %ld, >%s<\n", strlen(endptr), endptr);
                    malformed_exit("Could not parse number or math operation!");
                }

                execute_math_operation(&stack, token[0]);

            } else {
                stack_push(&stack, value);
            }

            token = strtok(NULL, " ");
        }

        //printf("result ");
        //print_stack(&stack);
        double res = stack_pop(&stack);
        if (!isnan(stack_pop(&stack))) {
            malformed_exit("There is more than one output number!");
        }
        fprintf(tmp_fp, "%.15g\n", res);
    }

    fclose(in_fp);
    rewind(tmp_fp);

    in_fp = fopen(input_file, "w");
    if (in_fp == NULL) {
        perror("Could not open output file");
        return EXIT_FAILURE;
    }

    while (getline(&line, &len, tmp_fp) != -1) {
        fprintf(in_fp, "%s", line);
    }

    free(line);
    fclose(in_fp);
    fclose(tmp_fp);

    return EXIT_SUCCESS;
}
