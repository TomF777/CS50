/* Program that calculates the approximate grade level needed to comprehend some text. 
The program should print as output “Grade X” where “X” is the grade level computed, rounded to the nearest integer. 
If the grade level is 16 or higher (equivalent to or greater than a senior undergraduate reading level), 
the program should output “Grade 16+” instead of giving the exact index number. 
If the grade level is less than 1, the program should output “Before Grade 1”.

Background:
So what sorts of traits are characteristic of higher reading levels? 
Longer words probably correlate with higher reading levels. Likewise, longer sentences probably correlate with higher reading levels, too.
A number of “readability tests” have been developed over the years that define formulas for computing the reading level of a text. 
One such readability test is the Coleman-Liau index. 
The Coleman-Liau index of a text is designed to output that (U.S.) grade level that is needed to understand some text. The formula is:

index = 0.0588 * L - 0.296 * S - 15.8

where L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.

*/
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// function prototypes
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // printf("number of letters: %i\n", count_letters(text));
    // printf("number of words: %i\n", count_words(text));
    // printf("number of sentences: %i\n", count_sentences(text));

    // Compute the Coleman-Liau index
    int index = (int) round(0.0588 * ((float) letters / (float) words * 100.0) -
                            0.296 * ((float) sentences / (float) words * 100.0) - 15.8);

    // Print the grade level
    // printf("Level: %i\n", index);
    if (index < 1)
        printf("Before Grade 1\n");
    else if (index > 16)
        printf("Grade 16+\n");
    else
        printf("Grade %i\n", index);
}

// *********************
// functions declaration
// *********************
int count_letters(string text)
{
    // Return the number of letters in text
    int letters = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // check if symbol in text array is a letter
        if (isalpha(text[i]))
        {
            letters++;
        }
    }

    return letters;
}

int count_words(string text)
{
    // Return the number of words in text

    // number of spaces in a text
    int spaces = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // check if symbol in text array is a space
        if (isspace(text[i]))
        {
            spaces++;
        }
    }
    return spaces + 1;
}

int count_sentences(string text)
{
    // Return the number of sentences in text

    int sentences = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // check if symbol in text array is a '.' '!' or '?' and succeeded character is a space or
        // NULL(end of string)
        if ((text[i] == '?' || text[i] == '!' || text[i] == '.') &&
            (text[i + 1] == '\0' || isspace(text[i + 1])))
        {
            sentences++;
        }
    }
    return sentences;
}

