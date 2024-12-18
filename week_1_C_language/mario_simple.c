/*
Implement a program in C that recreates that pyramid, using hashes (#) for bricks, as in the below:
       #
      ##
     ###
    ####
   #####
  ######
 #######
########

But prompt the user for an int for the pyramid’s actual height, so that the program can also output shorter pyramids like the below:
  #
 ##
###

Re-prompt the user, again and again as needed, if their input is not greater than 0 or not an int altogether.
*/

#include <cs50.h>
#include <stdio.h>

void print_row(int spaces, int bricks);

int main(void)
{
    int height;
    // prompt user for positive integer
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1);

    for (int i = 0; i < height; i++)
    {
        print_row(height - i - 1, i + 1);
    }
}

void print_row(int spaces, int bricks)
{
    for (int i = 0; i < spaces; i++)
        printf(" ");
    for (int j = 0; j < bricks; j++)
        printf("#");
    printf("\n");
}
