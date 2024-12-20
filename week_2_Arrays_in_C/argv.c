/* Program that prints each command-line argument given to the program
   It also converts arguments into integer
*/

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    for (int i = 0; i < argc; i++)
    {
        printf("argv[%i] is %s\n", i, argv[i]);
    }

    if (argc > 1)
    {
        int num_val1 = atoi(argv[1]);
        int num_val2 = atoi(argv[2]);
        printf("arg1: %i arg2: %i \n", num_val1, num_val2);
    }
}
