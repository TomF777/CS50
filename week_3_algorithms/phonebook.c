/*
Search algorithm on struct array
*/
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// data structure
typedef struct
{
    string name;
    string number;
} person;


int main(void)
{
    person people[3];
    people[0].name = "John";
    people[0].number = "+1-617-334-1999";

    people[1].name = "Carter";
    people[1].number = "+1-617-495-1999";

    people[2].name = "David";
    people[2].number = "+1-617-123-1000";

    string name = get_string("Name: ");
    for (int i = 0; i < 3; i++)
    {
        if (strcmp(people[i].name , name) == 0)
        {
            printf("Found %s\n", people[i].number);
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}


