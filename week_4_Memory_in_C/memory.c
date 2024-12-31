// Demonstrates memory errors via valgrind

#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int *x = malloc(3 * sizeof(int));       // array (3) of int
    x[1] = 72;
    x[2] = 73;
    x[3] = 33;

    // now call 'valgrind ./memory' to check the program

    // correct the code with following:
    // x[0]=72; x[1]=73; x[2]=33;
    // free(x)
}
