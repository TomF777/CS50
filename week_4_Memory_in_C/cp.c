// copy a file
// 1st command line argument: source file name
// 2nd command line argument: destination file name

#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    FILE *src = fopen(argv[1], "rb");   // open binary file to read
    FILE *dst = fopen(argv[2], "wb");   // open binary file to write

    BYTE b;

    while(fread(&b, sizeof(b), 1, src) != 0)
    {
        fwrite(&b, sizeof(b), 1, dst);
    }

    fclose(dst);
    fclose(src);
}
