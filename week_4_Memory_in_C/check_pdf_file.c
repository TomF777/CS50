/*
Program that opens a file given as a command-line argument
Check if that file is a PDF. A PDF always starts with a four-byte sequence,
corresponding to the integers: 37, 80, 68, 70
*/

#include <cs50.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // take exactly one argument
    if (argc != 2)
        return 1;

    // check if first four bytes exist in given file
    string filename = argv[1];
    FILE *file = fopen(filename, "r");

    uint8_t buffer[4];

    int blocks_read = fread(buffer, 1, 4, file);

    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", buffer[i]);
    }

    // check here if buffer[0]==37, buffer[1]==80, etc.
    
    printf("Blocks read: %i\n", blocks_read);
    fclose(file);
}
