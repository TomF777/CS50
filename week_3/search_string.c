/*
Search on string array
*/
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string strings[] = {"battle", "top hat", "iron", "boot", "cannon", "request", "fog"};

    string s = get_string("String: ");
    for (int i = 0; i < 7; i++)
    {
        if (strcmp(strings[i], s) == 0 )
        {
            printf("Found\n");
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}
