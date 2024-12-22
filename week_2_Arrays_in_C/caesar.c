/*
Caesar used to “encrypt” (i.e., conceal in a reversible way) confidential messages by shifting each letter therein by some number of places. 
For instance, he might write A as B, B as C, C as D, …, and, wrapping around alphabetically, Z as A. 
And so, to say HELLO to someone, Caesar might write IFMMP instead. 
Upon receiving such messages from Caesar, recipients would have to “decrypt” them by shifting letters in the opposite direction by the same number of places.

Formally, Caesar’s algorithm (i.e., cipher) encrypts messages by “rotating” each letter by 'k' positions.
More formally, if 'p' is some plaintext (i.e., an unencrypted message), 'pi' is the 'ith' character in 'p'
and 'k' is a secret key (i.e., a non-negative integer), then each letter 'ci', in the ciphertext, is computed as:
ci = (pi + k) % 26

- Program must accept a single command-line argument, a non-negative integer.
- If  program is executed without any command-line arguments or with more than one command-line argument, your program should print an error message.
- Program must output "plaintext:  " and then prompt the user for a string of plaintext.
- Program must output "ciphertext: " followed by the plaintext’s corresponding ciphertext, 
  with each alphabetical character in the plaintext “rotated” by k positions; non-alphabetical characters should be outputted unchanged.
- Program must preserve case: capitalized letters, though rotated, must remain capitalized letters; lowercase letters, though rotated, must remain lowercase letters.
*/

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
