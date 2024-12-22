/*
A substitution cipher,  “encrypts” (i.e., conceal in a reversible way) a message by replacing every letter with another letter. 
To do so, it uses a key: in this case, a mapping of each of the letters of the alphabet to the letter it should correspond to when it encrypts. 
To “decrypt” the message, the receiver of the message would need to know the key, so that they can reverse the process: 
translating the encrypt text (generally called ciphertext) back into the original message (generally called plaintext).

A key, for example, might be the string NQXPOMAFTRHLZGECYJIUWSKDVB.
This 26-character key means that A (the first letter of the alphabet) should be converted into N (the first character of the key), 
B (the second letter of the alphabet) should be converted into Q (the second character of the key), and so forth.

A message like HELLO, then, would be encrypted as FOLLE, replacing each of the letters according to the mapping determined by the key.

- The program must accept a single command-line argument, the key to use for the substitution. 
  The key itself should be case-insensitive, so whether any character in the key is uppercase or 
  lowercase should not affect the behavior of your program.

- If program is executed without any command-line arguments or with more than one command-line argument, 
  the program should print an error message and return from main a value 1.

- If the key is invalid (as by not containing 26 characters, containing any character that is not an alphabetic character,
  or not containing each letter exactly once), the program should print an error message and return from main a value 1.

- The program must output "plaintext: " (without a newline) and then prompt the user for a string of plaintext.

- The program must output "ciphertext: " (without a newline) followed by the plaintext’s corresponding ciphertext, 
  with each alphabetical character in the plaintext substituted for the corresponding character in the ciphertext; 
  non-alphabetical characters should be outputted unchanged.

- Program must preserve case: capitalized letters must remain capitalized letters; lowercase letters must remain lowercase letters.
- After outputting ciphertext, print a newline. The program should then exit by returning 0 from main.

*/
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// function prototypes
bool check_key_length(string s);
bool check_key_no_repeats_isalpha(string s);
void encipher(string plaintext, string key);

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // get the key
    string key = argv[1];

    // validate key; both functions must return true, otherwise exit the program
    if (!(check_key_length(key) && check_key_no_repeats_isalpha(key)))
    {
        // exit program if key in invalid
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Prompt user for plaintext if key is valid
    string plaintext = get_string("plaintext:  ");

    printf("ciphertext: ");

    // encrypt the plaintext with key
    encipher(plaintext, key);

    printf("\n");
    return 0;
}

bool check_key_length(string s)
{ // check key length and return true if exactly 26 characters
    if (strlen(s) != 26)
        return false;
    return true;
}

bool check_key_no_repeats_isalpha(string s)
{ // check if there are no repeated characters in a key and
  // all characters are alphabetical (return true, otherwise false)

    // As this is a second check after function call 'check_key_length'
    // we know that the key has for sure 26 characters (otherwise it exits program with return 1
    // before calling 'check_key_no_repeats_isalpha'), we can assume
    // constant value for char_counter size
    const int KEY_SIZE = 26;

    // indexes 0-25 in 'letter_counter' represent how many each letter occurs in a key
    int letter_counter[KEY_SIZE] = {0};

    // iterate through key
    for (int i = 0, length = strlen(s); i < length; i++)
    {
        // if any character is not alphabetical, skip the rest and return false from function call
        if (!isalpha(s[i]))
            return false;

        // In this case s[i] must be a letter and
        // map it to number 0-25 (a-z) and save occurence number.
        letter_counter[tolower(s[i]) - 97]++;
    }

    // check if any letter in key occured more then once
    for (int i = 0; i < KEY_SIZE; i++)
    {
        if (letter_counter[i] > 1)
            return false;
    }

    return true;
}

void encipher(string plaintext, string key)
{
    int offset = 0;
    char encrypt_sign;

    // For each character in the plaintext:
    for (int i = 0, length = strlen(plaintext); i < length; i++)
    {
        // indexed character in the plaintext
        char character = plaintext[i];

        // use encryption if character is alphabetical
        if (isalpha(character))
        {
            // lower case letter
            if (isupper(character))
            {
                offset = 65;
                // map plaintext character to character from key string
                encrypt_sign = toupper(key[character - offset]);
            }
            // lowercase letter
            else if (islower(character))
            {
                offset = 97;
                // map plaintext character to character from key string
                encrypt_sign = tolower(key[character - offset]);
            }
        }
        else
        { // no character encryption if character is not a letter
            encrypt_sign = character;
        }

        printf("%c", encrypt_sign);
    }
}
