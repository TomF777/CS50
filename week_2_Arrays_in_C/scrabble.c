/*
In the game of Scrabble, players create words to score points, and the number of points is the sum of the point values of each letter in the word.

A B C D E F G H I J K L M N O P Q  R S T U V W X Y Z
1 3 3 2 1 4 2 4 1 8 5 1 3 1 1 3 10 1 1 1 1 4 4 8 4 10

The program should prompt for input twice: once for “Player 1” to input their word and once for “Player 2” 
to input their word. 
Then, depending on which player scores the most points, 
the program should either print “Player 1 wins!”, “Player 2 wins!”, or “Tie!” (in the event the two players score equal points).

*/

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Prompt the user for two words
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Compute the score of each word
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    printf("score1: %i  score2: %i\n", score1, score2);

    // Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // Compute and return score for word

    // Keep track of score
    int score = 0;

    // declare symbol in uppercase
    int symbol = 0;

    // Compute score for each character
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        // convert each character to uppercase if possible
        symbol = toupper(word[i]);

        // check if tested sign is a letter
        if (symbol >= 65 && symbol <= 90)
        {
            score += POINTS[symbol - 'A'];
        }
    }

    return score;
}
