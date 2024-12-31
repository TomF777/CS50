// print integers with pointer arithemtic
 
#include <stdio.h>

int main(void)
{
    int n = 50;

    // &n = address of the variable
    // *p = pointer declaration of variable that stores the address = Instructs the compiler to go to a location in memory
    int *p = &n;

    // pointer and dereference
    printf("%p\n", &n);
    printf("%p\n", p);
    printf("%i\n", *p); // go to the pointer location
}
