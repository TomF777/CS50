/* Program to check if an array of characters is in
   alphabetical order.
   All characters can be lowercase or uppercase
*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


string convert_string_to_uppercase(string s);

int main(void)
{
    string phrase = get_string("Enter a phrase: ");

    phrase = convert_string_to_uppercase(phrase);
    for (int i = 0, length = strlen(phrase); i < length - 1; i++)
    {
        printf("%c ", phrase[i]);
        printf("%i ", phrase[i]);

        // check if characters are not alphabetical
        if (phrase[i] > phrase[i + 1])
        {
            printf("\nNot in alphabetical order\n");
            return 0;
        }
    }
    printf("\nAlphabetical order\n");
    return 0;
}

string convert_string_to_uppercase(string s)
{

    for (int i = 0, length = strlen(s); i < length; i++ )
    {
        s[i] = toupper(s[i]);
    }
    return s;
}
