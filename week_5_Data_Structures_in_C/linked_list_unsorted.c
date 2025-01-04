// implements a list of numbers using a linked list (append each number as node)
// the numbers are not sorted

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

        // if list is empty
        if (list == NULL)
        {
            // this node is the whole list
            list = n;
        }
        // if list has numbers already
        else
        {
            // iterate over nodes in list
            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                //if at the end of list
                if (ptr->next == NULL)
                {
                    // append node
                    ptr->next = n;
                    break;
                }
            }
        }
    }

    // print whole list
    node *ptr = list;
    while (ptr != NULL)
    {
        printf("%i\n", ptr->number);
        ptr = ptr->next;
    }

}
