// when array not cleared, 
// it depicts garbage data in some array's field 

#include <stdio.h>


int main(void)
{
    int scores[1024];
    for (int i = 0; i < 1024; i++)
    {
        printf("%i\n", scores[i]);
    }

}
