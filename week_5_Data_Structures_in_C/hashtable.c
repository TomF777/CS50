/*
Function `hash` should return number 0-25,
depending on the first character of the word.
*/

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node
{
    string phrase;
    struct node *next;
} node;

node *table[26];

int hash(string phrase);


int main(void)
{
    // Add items
    for (int i = 0; i < 3; i++)
    {
        string phrase = get_string("Enter a new phrase: ");

        // Find phrase bucket
        int bucket = hash(phrase);
        printf("%s hashes to %i\n", phrase, bucket);
    }
}

// return the correct bucket for a given phrase
int hash(string phrase)
{
    return toupper(phrase[0]) - 'A';
}


