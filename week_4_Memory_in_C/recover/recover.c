#include <cs50.h>
#include <stdint.h>
#include <stdio.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{

    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");

    // Create a buffer for a block of data
    uint8_t buffer[BLOCK_SIZE];

    char filename[8];

    // jpg files numbering
    int jpg_number = 0;

    // at least one jpg found
    bool jpg_found = false;

    // ptr to jpg file
    FILE *jpg_file;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        // JPEG start found
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // its already not the first jpg
            if (jpg_number > 0)
            {
                // close previous jpg file
                fclose(jpg_file);
            }

            // Create JPEGs name with increasining jpg_number
            sprintf(filename, "%03i.jpg", jpg_number);

            // open new jpg file
            jpg_file = fopen(filename, "w");

            // write buffer content into jpg file
            fwrite(buffer, 1, BLOCK_SIZE, jpg_file);

            jpg_found = true;
            jpg_number++;
        }
        else
        {
            if (jpg_found == true)
                fwrite(buffer, 1, BLOCK_SIZE, jpg_file);
        }
    }

    // close last jpg file
    fclose(jpg_file);

    // close memory card file
    fclose(card);
}
