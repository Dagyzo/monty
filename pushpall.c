#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define UNUSED(x) (void)(x)

typedef struct stack_s {
    int n;
    struct stack_s *next;
} stack_t;

stack_t *stack = NULL;

void push(int n, unsigned int line_number)
{
    stack_t *new_node = malloc(sizeof(stack_t));
    if (!new_node)
    {
        printf("Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->n = n;
    new_node->next = stack;
    stack = new_node;
    UNUSED(line_number);
}

void pall(unsigned int line_number)
{
    stack_t *temp = stack;
    UNUSED(line_number);
    while (temp)
    {
        printf("%d\n", temp->n);
        temp = temp->next;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    char *line = NULL;
    size_t len = 0;
    unsigned int line_number = 0;
    while (getline(&line, &len, file) != -1)
    {
        line_number++;
        char *opcode = strtok(line, " \n\t");
        if (opcode && opcode[0] != '#')
        {
            if (strcmp(opcode, "push") == 0)
            {
                char *arg = strtok(NULL, " \n\t");
                if (arg && isdigit(arg[0]))
                {
                    push(atoi(arg), line_number);
                }
                else
                {
                    printf("L%d: usage: push integer\n", line_number);
                    exit(EXIT_FAILURE);
                }
            }
            else if (strcmp(opcode, "pall") == 0)
            {
                pall(line_number);
            }
            else
            {
                printf("L%d: unknown instruction %s\n", line_number, opcode);
                exit(EXIT_FAILURE);
            }
        }
    }

    free(line);
    fclose(file);

    return EXIT_SUCCESS;
}
