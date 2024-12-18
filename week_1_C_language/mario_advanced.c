/*
Implement a program in C that recreates that pyramid, using hashes (#) for bricks, as in the below:

   #  #
  ##  ##
 ###  ###
####  ####

And let’s allow the user to decide just how tall the pyramids should be by first prompting them for a positive int between, say, 1 and 8, inclusive.

*/


#include <cs50.h>
#include <stdio.h>

void print_row_right(int spaces, int bricks);
void print_row_left(int length);

int main(void)
{

    int height;

    // prompt user for positive integer between 1 and 8 inclusive
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int i = 0; i < height; i++)
    {

        print_row_right(height - i - 1, i + 1);
        printf("  ");
        print_row_left(i + 1);
        printf("\n");
    }
}

// *********************
// function declarations
// **********************
void print_row_right(int spaces, int bricks)
{
    // print right assigned row

    for (int i = 0; i < spaces; i++)
        printf(" ");
    for (int j = 0; j < bricks; j++)
        printf("#");
}

void print_row_left(int length)
{
    // print left assigned row

    for (int i = 0; i < length; i++)
    {
        printf("#");
    }
}
