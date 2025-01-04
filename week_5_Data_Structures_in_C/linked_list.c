// Prepends numbers to a linked list, using while loop to print

#include <stdio.h>
#include <stdlib.h>


typedef struct node
{
    int number;
    struct node *next;
} node;


int main(int argc, char *argv[])
{
    // memory for numbers
    node *list = NULL;

    // iterate each command-line argument
    for(int i = 1; i < argc; i++)
    {
        int number = atoi(argv[i]);
        printf("%i\n", number);

        // allocate node for number
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            // free memory
            return 1;
        }
        n->number = number;
        n->next = NULL;

        //prepend node to list
        n->next = list;
        list = n;
    }

    // print whole list
    node *ptr = list;
    while (ptr != NULL)
    {
        printf("%i\n", ptr->number);
        ptr = ptr->next;
    }

    // Free memory
    ptr = list;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
}
