/*
The program adds a node to the linked list and
ensures that list always points to the head of the linked list.

The function `unload` frees all nodes in the linked list.
Return true when successful
*/

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    string phrase;
    struct node *next;
} node;

#define LIST_SIZE 2

bool unload(node *list);
void visualizer(node *list);

int main(void)
{
    node *list = NULL;

    // add items to list
    for (int i = 0; i < LIST_SIZE; i++)
    {
        string phrase = get_string("Enter a new phrase ");

        // add phrase to new node in list
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            // error allocating memory
            return 1;
        }

        n->phrase = phrase;
        n->next = list;
        list = n;

        // visulize list after adding a node
        visualizer(list);
    }

    // free all memory used
    if (!unload(list))
    {
        printf("Error freeing the list\n");
        return 1;
    }

    printf("Freed the list\n");
    return 0;

}

bool unload(node *list)
{
    // free all alocated nodes
    node *ptr = list;

    while (ptr != NULL)
    {
        ptr = list->next;
        free(list);
        list = ptr;
    }
    return true;
}

void visualizer(node *list)
{
    printf("\n+== List Visualizer --+\n\n");
    while (list != NULL)
    {
        printf("Location %p\nPhrase: \"%s\"\nNext: %p\n\n", list, list->phrase, list->next);
        list = list->next;
    }
    printf("+---------------------+\n\n");
}
