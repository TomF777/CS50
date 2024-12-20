#include <ctype.h>
#include <cs50.h>
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

    //printf("number of letters: %i\n", count_letters(text));
    //printf("number of words: %i\n", count_words(text));
    //printf("number of sentences: %i\n", count_sentences(text));

    // Compute the Coleman-Liau index
    int index = (int)round(0.0588 * ((float)letters / (float)words * 100.0) - 0.296 * ((float)sentences / (float)words * 100.0) - 15.8);

    // Print the grade level
    // printf("Level: %i\n", index);
    if (index < 1) printf("Before Grade 1\n");
    else if (index > 16) printf("Grade 16+\n");
    else printf("Grade %i\n", index);

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
        // check if symbol in text array is a '.' '!' or '?' and succeeded character is a space or NULL(end of string)
        if ((text[i] == '?' || text[i] == '!' || text[i] == '.') && (text[i + 1] == '\0' || isspace(text[i + 1]) ))
        {
            sentences++;
        }
    }
    return sentences;
}
