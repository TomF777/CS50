#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{

    // Make sure program was run with just one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Make sure every character in argv[1] is a digit
    bool result =  only_digits(argv[1]);
    if (!result)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }


    // Convert argv[1] from a `string` to an `int`
    int key = atoi(argv[1]);

    // Prompt user for plaintext
    string plaintext = get_string("plaintext:  ");


    printf("ciphertext: ");
    char encrypt_sign;

    // For each character in the plaintext:
    for (int j = 0, length = strlen(plaintext); j < length; j++)
    {
        // Rotate the character if it's a letter
        if isalpha(plaintext[j])
        {
            encrypt_sign = rotate(plaintext[j], key);
        }
        else
        {
            encrypt_sign = plaintext[j];
        }
        printf("%c", encrypt_sign);
    }
    printf("\n");
}

// ********************
// functions declaration
// ********************
bool only_digits(string s)
{
    for (int i = 0, length = strlen(s); i < length; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

char rotate(char c, int n)
{
    char result = 0;
    int offset = 0;
    // uppercase letter
    if (isupper(c))
    {
        offset = 65;
    }
    // lowercase letter
    else if (islower(c))
    {
        offset = 97;
    }

    // cipher formula
    result = ((c - offset + n) % 26) + offset;
    return result;
}
